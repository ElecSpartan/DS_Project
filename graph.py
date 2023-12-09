class Graph:
    def __init__(self):
        self.users = []
        self.followers_of_user = {}  # {user_id(string) : list of ids(strings)}

    def add_user(self, user_id, user):
        # can there be 2 users with same id?
        self.users[user_id] = user
        self.followers_of_user[user_id] = []

    def add_follower(self, user_id, follower_id):
        # Assuming distinct ids?
        self.followers_of_user[user_id].append(follower_id)
