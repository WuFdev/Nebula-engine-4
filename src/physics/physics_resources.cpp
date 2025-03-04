#include <cooking/PxConvexMeshDesc.h>
#include <foundation/PxIO.h>
#include <geometry/PxTriangleMesh.h>
#include <PxMaterial.h>
#include <PxPhysics.h>

#include "physics_resources.h"
#include "engine/log.h"
#include "engine/lua_wrapper.h"
#include "engine/profiler.h"
#include "engine/resource_manager.h"
#include "engine/stream.h"
#include "engine/string.h"
#include "engine/math.h"
#include "physics/physics_system.h"


namespace Lumix
{


struct InputStream final : physx::PxInputStream
{
	InputStream(InputMemoryStream& blob) : blob(blob) {}

	physx::PxU32 read(void* dest, physx::PxU32 count) override {
		if (blob.read(dest, count)) return count;
		return 0;
	}

	InputMemoryStream& blob;
};


const ResourceType PhysicsGeometry::TYPE("physics_geometry");


PhysicsGeometry::PhysicsGeometry(const Path& path, ResourceManager& resource_manager, PhysicsSystem& system, IAllocator& allocator)
	: Resource(path, resource_manager, allocator)
	, system(system)
	, convex_mesh(nullptr)
	, tri_mesh(nullptr)
{
}

PhysicsGeometry::~PhysicsGeometry() = default;


bool PhysicsGeometry::load(u64 size, const u8* mem)
{
	PROFILE_FUNCTION();
	Header header;
	InputMemoryStream file(mem, size);
 	file.read(&header, sizeof(header));

	if (header.m_magic != HEADER_MAGIC) {
 		logError("Corrupted geometry ", getPath());
 		return false;
 	}
 
	if (header.m_version <= (u32)Versions::COOKED) {
		logError(getPath(), ": built version too old, please rebuild your data.");
		return false;
	}

	if (header.m_version > (u32)Versions::LAST) {
		logError("Unsupported version of geometry ", getPath());
		return false;
	}


	const bool is_convex = header.m_convex != 0;
	InputStream read_buffer(file);
	if (is_convex) {
		convex_mesh = system.getPhysics()->createConvexMesh(read_buffer);
	} else {
		tri_mesh = system.getPhysics()->createTriangleMesh(read_buffer);
 	}
 
	return true;
}


void PhysicsGeometry::unload()
{
	if (convex_mesh) convex_mesh->release();
	if (tri_mesh) tri_mesh->release();
	convex_mesh = nullptr;
	tri_mesh = nullptr;
}


PhysicsMaterial::PhysicsMaterial(const Path& path, ResourceManager& resource_manager, PhysicsSystem& system, IAllocator& allocator)
	: Resource(path, resource_manager, allocator) 
	, system(system)
{
	material = system.getPhysics()->createMaterial(0.5f, 0.5f, 0.1f);
}

PhysicsMaterial::~PhysicsMaterial() {
	if (material) {
		material->release();
		material = nullptr;
	}
}

ResourceType PhysicsMaterial::TYPE("physics_material");

void PhysicsMaterial::unload() {}

namespace LuaAPI {
	int static_friction(lua_State* L) {
		lua_getfield(L, LUA_GLOBALSINDEX, "this");
		PhysicsMaterialLoadData* material = (PhysicsMaterialLoadData*)lua_touserdata(L, -1);
		lua_pop(L, 1);

		material->static_friction = LuaWrapper::checkArg<float>(L, 1);

		return 0;
	}

	int dynamic_friction(lua_State* L) {
		lua_getfield(L, LUA_GLOBALSINDEX, "this");
		PhysicsMaterialLoadData* material = (PhysicsMaterialLoadData*)lua_touserdata(L, -1);
		lua_pop(L, 1);

		material->dynamic_friction = LuaWrapper::checkArg<float>(L, 1);

		return 0;
	}

	int restitution(lua_State* L) {
		lua_getfield(L, LUA_GLOBALSINDEX, "this");
		PhysicsMaterialLoadData* material = (PhysicsMaterialLoadData*)lua_touserdata(L, -1);
		lua_pop(L, 1);

		material->restitution = LuaWrapper::checkArg<float>(L, 1);

		return 0;
	}
} // namespace LuaAPI

bool PhysicsMaterial::load(u64 size, const u8* mem) {
	PhysicsMaterialManager& mng = static_cast<PhysicsMaterialManager&>(getResourceManager());
	PhysicsMaterialLoadData tmp;
	lua_State* L = mng.getState(tmp);

	const Span<const char> content((const char*)mem, (u32)size);
	if (!LuaWrapper::execute(L, content, getPath().c_str(), 0)) {
		return false;
	}

	material->setStaticFriction(tmp.static_friction);
	material->setDynamicFriction(tmp.dynamic_friction);
	material->setRestitution(tmp.restitution);

	return true;
}

PhysicsMaterialManager::PhysicsMaterialManager(PhysicsSystem& system, IAllocator& allocator)
	: ResourceManager(allocator)
	, system(system)
	, allocator(allocator)
{
	state = luaL_newstate();
	#define DEFINE_LUA_FUNC(func) \
		lua_pushcfunction(state, LuaAPI::func); \
		lua_setfield(state, LUA_GLOBALSINDEX, #func); 
	
	DEFINE_LUA_FUNC(static_friction);
	DEFINE_LUA_FUNC(dynamic_friction);
	DEFINE_LUA_FUNC(restitution);

	#undef DEFINE_LUA_FUNC
}

PhysicsMaterialManager::~PhysicsMaterialManager() {
	lua_close(state);
}

lua_State* PhysicsMaterialManager::getState(PhysicsMaterialLoadData& material) {
	lua_pushlightuserdata(state, &material);
	lua_setfield(state, LUA_GLOBALSINDEX, "this");
	return state;
}

Resource* PhysicsMaterialManager::createResource(const Path& path) {
	return LUMIX_NEW(m_allocator, PhysicsMaterial)(path, *this, system, allocator);
}

void PhysicsMaterialManager::destroyResource(Resource& resource) {
	LUMIX_DELETE(m_allocator, static_cast<PhysicsMaterial*>(&resource));
}

} // namespace Lumix