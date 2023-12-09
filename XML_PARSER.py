from USER import User, Post
from graph import Graph


def read_file(address):
    # address should be (r'absolute address') #
    with open(address, 'r') as file:
        initial_file = file.read()
        print(initial_file)
        return initial_file


def write_file(address, last_file):
    # address should be (r'absolute address') #
    with open(address, 'w') as file:
        file.write(last_file)


def parsing_with_correcting_errors(address):
    initial_file = read_file(address)
    end_file = ""
    line_num = 1
    expected = ['<users>', '<user>', '<id>', '<name>', '<posts>', '<post>', '<body>', '<topics>', '<topic>',
                '<followers>', '<follower>', '<id>']
    expected_index = 0
    last_opening = []
    next_is_opening = 1
    next_is_closing = 0

    idd = ""
    name = ""
    body = ""
    topics = []
    posts = []
    followers_ids = []
    first_id = 1
    g = Graph()
    index = 0
    while index < len(initial_file):

        c = initial_file[index]

        if c == ' ' or c == '\n':
            end_file = end_file + c
            if c == '\n':
                line_num += 1

            index += 1
            continue

        if next_is_opening or next_is_closing:
            if initial_file[index + 1] == '/':
                next_is_opening = 0
                next_is_closing = 1
            else:
                next_is_opening = 1
                next_is_closing = 0

        if next_is_opening and (not next_is_closing):
            last_opening.append(expected[expected_index])
            for ch in expected[expected_index]:
                end_file = end_file + ch
                index += 1

            # 1)
            # how to know error??
            # no_error = 1
            # for i in range(len(expected[expected_index])):
            # no_error = no_error and (expected[expected_index][i] == initial_file[index])
            # index += 1

            if expected[expected_index] == '<id>' or expected[expected_index] == '<name>' or expected[
                expected_index] == '<body>' or expected[expected_index] == '<topic>':
                next_is_opening = 0
                next_is_closing = 0

            if expected_index != 8 and expected_index != 11:
                expected_index += 1

            elif expected_index == 11:
                expected_index -= 1



        elif not next_is_opening and not next_is_closing:
            txt = ""
            while initial_file[index] != '<':
                end_file = end_file + initial_file[index]
                txt = txt + initial_file[index]
                if initial_file[index] == '\n':
                    line_num += 1

                index += 1

            if last_opening[-1] == '<id>':
                if first_id:
                    first_id = 0
                    idd = txt.strip()
                else:
                    followers_ids.append(txt)
            elif last_opening[-1] == '<name>':
                name = txt.strip()
            elif last_opening[-1] == '<body>':
                body = txt.strip()
            elif last_opening[-1] == '<topic>':
                topics.append(txt.strip())

            next_is_opening = 0
            next_is_closing = 1


        else:
            # 1)
            # error checking
            # how to??

            open_tag = last_opening[-1]
            close_tag = open_tag[0] + '/' + open_tag[1:]
            index += len(close_tag)
            last_opening.pop()
            for ch in close_tag:
                end_file = end_file + ch

            if close_tag == '</post>':
                post1 = Post(body, topics)
                posts.append(post1)
                body = ""
                topics = []

            elif close_tag == '</user>':
                user = User(idd, name, posts)
                g.add_user(idd, user)
                for x in followers_ids:
                    g.add_follower(idd, x)

                first_id = 1
                idd = ""
                name = ""
                posts = []
                followers_ids = []

            elif close_tag == '</topics>':
                expected_index = 5

            elif close_tag == '</posts>':
                expected_index = 9

            elif close_tag == '</followers>':
                expected_index = 1

            elif close_tag == '</users>':
                break

            next_is_opening = 1
            next_is_closing = 0

    return end_file, g


end_file, g = parsing_with_correcting_errors(r'E:\College\Data structures\Project\DS_Project\sample.xml')
print('\n****************************\n')
print(end_file)

