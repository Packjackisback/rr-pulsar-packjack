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

    Friends();
    ~Friends();
    Friends(const Friends &) = delete;
    Friends &operator=(const Friends &) = delete;

    void Load(ConfigFile &conf);
    void Save(ConfigFile &conf);

    u32 GetFriendCount() const;
    u64 GetFriendCode(u32 idx) const;
    u32 GetFriendStatus(u32 idx) const;
    u32 AddFriend(u64 friendCode, u32 status);
    void RemoveFriend(u32 idx);
    u32 FindFriendIdx(u64 friendCode) const;
    bool IsFriend(u64 friendCode) const;

    static const u32 FriendCapacity;

private:
    FriendsHolder friends;
};

}  // namespace Pulsar

#endif
