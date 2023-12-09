class User:
    def __init__(self, user_id, name, posts):
        self.user_id = user_id  # string
        self.name = name  # string
        self.posts = posts  # list of posts


class Post:
    def __init__(self, body, topics):
        self.body = body  # string
        self.topics = topics  # list of strings
