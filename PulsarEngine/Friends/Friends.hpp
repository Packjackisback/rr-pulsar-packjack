#ifndef _PULSARFRIENDS_
#define _PULSARFRIENDS_
#include <kamek.hpp>
#include <Config.hpp>
#include <PulsarSystem.hpp>

namespace Pulsar {

class Friends {
public:
    static Friends *sInstance;
    static Friends *CreateInstance();
    static void DestroyInstance();
    static void RequestSave();
    static void SaveTask(void *data);

    Friends();
    ~Friends();
    Friends(const Friends &) = delete;
    Friends &operator=(const Friends &) = delete;

    void Load(const ConfigFile &conf);
    void Save(const ConfigFile &conf);

    u32 GetFriendCount() const;
    u64 GetFriendCode(u32 idx) const;
    u32 GetFriendStatus(u32 idx) const;
    u32 AddFriend(u64 friendCode, u32 status);
    void RemoveFriend(u32 idx);
    u32 FindFriendIdx(u64 friendCode) const;
    bool IsFriend(u64 friendCode) const;

    void MarkDirty();
    bool IsDirty() const;

    static const u32 FriendCapacity;

private:
    friend class System;

    const ConfigFile *conf;
    FriendsHolder friends;
    bool dirty;
};

}  // namespace Pulsar

#endif
