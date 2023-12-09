class Graph:
    def __init__(self):
        self.users = {}
        self.followers_of_user = {}  # {user_id(string) : list of ids(strings)}
        self.visited = set()

    def add_user(self, user_id, user):
        # can there be 2 users with same id?
        self.users[int(user_id)] = user
        self.followers_of_user[int(user_id)] = []

    def add_follower(self, user_id, follower_id):
        # Assuming distinct ids?
        self.followers_of_user[int(user_id)].append(follower_id)

    def dfs(self, start_user_id):
        self.visited.add(start_user_id)
        print(f"Visiting user {start_user_id}")

        for follower_id in self.followers_of_user[start_user_id]:
            if follower_id not in self.visited:
                self.dfs(int(follower_id))