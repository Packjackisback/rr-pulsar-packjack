#include <Friends/Friends.hpp>

namespace Pulsar {

Friends *Friends::sInstance = nullptr;

Friends *Friends::CreateInstance() {
    Friends *self = Friends::sInstance;
    if (self == nullptr) {
        self = new (System::sInstance->heap, 0x20) Friends;
        Friends::sInstance = self;
    }
    return self;
}

void Friends::DestroyInstance() {
    delete Friends::sInstance;
    Friends::sInstance = nullptr;
}

Friends::Friends() {
    memset(&this->friends, 0, sizeof(FriendsHolder));
    this->friends.friendCount = 0;
}

Friends::~Friends() {
}

void Friends::Load(ConfigFile &conf) {
    this->friends = conf.GetSection<FriendsHolder>();
}

void Friends::Save(ConfigFile &conf) {
    void *dest = ut::AddU32ToPtr(static_cast<void *>(&conf), static_cast<u32>(conf.header.offsets[FriendsHolder::index]));
    memcpy(dest, &this->friends, sizeof(FriendsHolder));
}

u32 Friends::GetFriendCount() const {
    return this->friends.friendCount;
}

u64 Friends::GetFriendCode(u32 idx) const {
    return this->friends.friends[idx].friendCode;
}

u32 Friends::GetFriendStatus(u32 idx) const {
    return this->friends.friends[idx].status;
}

u32 Friends::AddFriend(u64 friendCode, u32 status) {
    FriendsHolder &holder = this->friends;
    if (holder.friendCount >= FriendsHolder::capacity)
        return 0xFFFFFFFF;  // friend list is full
    const u32 idx = holder.friendCount;
    holder.friends[idx].friendCode = friendCode;
    holder.friends[idx].status = status;
    holder.friendCount = idx + 1;
    return idx;
}

void Friends::RemoveFriend(u32 idx) {
    FriendsHolder &holder = this->friends;
    if (idx < holder.friendCount) {
        for (u32 i = idx; i + 1 < holder.friendCount; ++i) {
            holder.friends[i] = holder.friends[i + 1];
        }
        --holder.friendCount;
    }
}

u32 Friends::FindFriendIdx(u64 friendCode) const {
    const FriendsHolder &holder = this->friends;
    for (u32 i = 0; i < holder.friendCount; ++i) {
        if (holder.friends[i].friendCode == friendCode)
            return i;
    }
    return 0xFFFFFFFF;
}

bool Friends::IsFriend(u64 friendCode) const {
    return this->FindFriendIdx(friendCode) != 0xFFFFFFFF;
}

const u32 Friends::FriendCapacity = FriendsHolder::capacity;

}  // namespace Pulsar
