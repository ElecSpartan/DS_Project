class Graph:
    def __init__(self):
        self.users = {}
        self.followers_of_user = {}  # {user_id(int) : list of ids(int)}
        self.visited = set()

    def add_user(self, user_id, user):
        # can there be 2 users with same id?
        self.users[int(user_id)] = user
        self.followers_of_user[int(user_id)] = []

    def add_follower(self, user_id, follower_id):
        # Assuming distinct ids?
        self.followers_of_user[int(user_id)].append(int(follower_id))

