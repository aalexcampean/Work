from Console.Ui import Ui
from Entity.Player import Player
from Repository.Player_Repo import PlayerRepository
from Service.Player_Service import PlayerService
from Service.Tournament_Inner_Workings import TournamentWorkings

def read_players_input_file(file_name):
    result = []
    f = open(file_name, "r")
    line = f.readline()
    while len(line) > 0:
        line = line.split(",")
        result.append(Player(int(line[0]), line[1], int(line[2])))
        line = f.readline().strip()
    f.close()
    return result


players = read_players_input_file('Players.txt')

players_repo = PlayerRepository(players)
player_service = PlayerService(players_repo)

tournament = TournamentWorkings

ready = Ui(player_service, tournament)
ready.start_ui()
