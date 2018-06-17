/* 1) basic chatting implementation
 2)chatting room
 3)room changing
 4)leave message
 5)listing users
 6)solving nickname duplication
 7)connection health checking
 */
#include <cstdio>
# include <cstdlib>

#include <netdb.h>
#include <netinet/in.h>

#include <cstring>
#include <thread>
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <unistd.h>


using namespace std;

struct User {
  string name;
  int socket;
  string room;
  User(string _name, string _room, int _socket) : name(_name), room(_room), socket(_socket) {}

};

struct Room {
  string name;
  vector <User> vuser;
  Room() : name(""), vuser(vector<User>()) { }
  Room(string _name, User user) {
    vuser.push_back(user);
    name = _name;
  }
};

vector <thread> threads;
map<string, Room> room;
map<string, int> socket_map;
map<string, int> cnt_name;



void Send(User user, string msg, bool all, vector<string> user_list) {
  vector<int> socket_list;

  if (all) {
    for (int i = 0; i < room[user.room].vuser.size(); i++) {
      if(room[user.room].vuser[i].name != user.name) {
        send(room[user.room].vuser[i].socket, msg.c_str(), msg.size(), 0);
        sleep(1);
      }
    }
  }



  else {
    vector < string > not_exist;
    for (int i = 0; i < user_list.size(); i++) {
      if (socket_map.count(user_list[i])) {
        send(socket_map[user_list[i]], msg.c_str(), msg.size(), 0);
        sleep(1);
      } else {
        not_exist.push_back(user_list[i]);
      }
    }


    msg = "NEWMSG$There is no such user : ";
    for (int i = 0; i < (int) not_exist.size() - 1; i++)
      msg += not_exist[i] + ", ";
    if (!not_exist.empty()) {
      msg += not_exist.back();
      send(user.socket, msg.c_str(), msg.size(), 0);
      sleep(1);
    }
  }

}

void erase_user(User user) {
  for(int i = 0; i < room[user.room].vuser.size(); i++) {
    if(room[user.room].vuser[i].name == user.name) {
      room[user.room].vuser.erase(room[user.room].vuser.begin() + i);
    }
  }
  socket_map.erase(user.name);
  return;
}

void main_activity(int socket) {

  /*struct timeval timeout;
  timeout.tv_sec = 2;
  timeout.tv_usec = 0;
  setsockopt(socket, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));*/

  User user = User("Noone", "1", 0);
  while(1) {
    char buffer[1000];
    bzero(buffer, sizeof(buffer));
    int recv_len = recv(socket, buffer, sizeof(buffer), 0);
    if(recv_len <= 0) {
      string new_msg = "NEWMSG$" + user.name + " is disconnected from room #" + user.room;
      Send(user, new_msg, true, vector<string>());
      erase_user(user);
      return;
    }

    string msg[1000];
    int msg_sz = 0;

    for(int i = 0; buffer[i] != '\0'; i++) {
      if(buffer[i] == '\n')
        msg_sz++;
      else
        msg[msg_sz].push_back(buffer[i]);
    } msg_sz++;

    if(msg[0] == "CHECK") {
      continue;
    }
    if(msg[0] == "NEWUSER") {
      if(!cnt_name.count(msg[1]))
        cnt_name[msg[1]] = 0;
      else
        cnt_name[msg[1]]++;

      if(cnt_name[msg[1]] > 0)
        msg[1] += "-" + to_string(cnt_name[msg[1]]);

      user = User(msg[1], msg[2], socket);
      socket_map[user.name] = socket;
      if(!room.count(msg[2])) {
        room[msg[2]] = Room(msg[2], user);
      }
      else {
        room[msg[2]].vuser.push_back(user);
      }

      string new_msg = "NEWMSG$Hello " + msg[1] + "! This is room #" + msg[2];
      send(socket, new_msg.c_str(), new_msg.size(), 0);
      sleep(1);

      new_msg = "NEWMSG$" + msg[1] + " joined room #" + msg[2];

      Send(user, new_msg, true, vector<string>());
    }
    if(msg[0] == "NEWMSG") {
      string new_msg = "NEWMSG$" + user.name + " : " + msg[msg_sz - 1];

      if(msg[1] == "ALL")
        Send(user, new_msg, true, vector<string>());
      else {
        vector < string > user_list;
        cout << "user list : ";
        for(int i = 2; i < (int)msg_sz - 2; i++) {
          cout << msg[i] << ' ';
          user_list.push_back(msg[i]);
        }
        cout << endl;
        Send(user, new_msg, false, user_list);
      }
    }
    if(msg[0] == "QUIT") {
      string new_msg = "NEWMSG$" + user.name + " is disconnected from room #" + user.room;
      Send(user, new_msg, true, vector<string>());
      new_msg = "QUIT$Good bye " + user.name;
      send(user.socket, new_msg.c_str(), new_msg.size(), 0);
      sleep(1);
      erase_user(user);
      return;
    }
    if(msg[0] == "LIST") {
      cout << "SALAM" << endl;
      string new_msg = "NEWMSG$This is list of users in room #" + user.room;
      for(int i = 0; i < room[user.room].vuser.size(); i++) {
        new_msg += "\n" + to_string(i + 1) + ". " + room[user.room].vuser[i].name;
      }
      send(user.socket, new_msg.c_str(), new_msg.size(), 0);
      sleep(1);
    }
    if(msg[0] == "JOIN") {
      string new_msg = "NEWMSG$" + user.name + " is disconnected from room #" + user.room;
      Send(user, new_msg, true, vector<string>());
      erase_user(user);
      user.room = msg[1];
      socket_map[user.name] = socket;
      if(!room.count(msg[1])) {
        room[msg[1]] = Room(msg[1], user);
      }
      else {
        room[msg[1]].vuser.push_back(user);
      }
      new_msg = "NEWMSG$Room changed to room #" + msg[1];
      send(socket, new_msg.c_str(), new_msg.size(), 0);
      sleep(1);
    }
  }

}



int main(int argc, char *argv[]) {
    cout << "Port number is set to 5001" << endl;
    cout << "Please use space before and after semicolon ':' while sending messages" << endl;
  int sockfd, newsockfd, portno;
  socklen_t clilen;
  char buffer[256];
  struct sockaddr_in serv_addr, cli_addr;
  int n;
  map<string, int> room_assigned;

  bzero((char *) &serv_addr, sizeof(serv_addr));
  portno = 5001;

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(portno);

  clilen = sizeof(cli_addr);

  // TODO : create socket and get file descriptor
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if(sockfd < 0) {
    puts("Error on opening socket");
    return 0;
  }

  // TODO : Now bind the host address using bind() call.
  if(::bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
    puts("Error on binding");
    return 0;
  }
  // TODO : start listening for the clients,
  // here process will go in sleep mode and will wait for the incoming connection
  listen(sockfd, 5);


  // TODO : inside this while loop, implement communicating with read/write or send/recv function
  while (1) {
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
    if(newsockfd < 0) {
      puts("Error on accept");
      return 0;
    }

    threads.push_back(thread(main_activity, newsockfd));

  }

  for(int i = 0; i < threads.size(); i++)
    threads[i].join();
  return 0;
}
