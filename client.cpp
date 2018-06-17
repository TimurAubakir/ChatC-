#include <stdio.h>
#include <stdlib.h>

#include <netdb.h>
#include <netinet/in.h>

#include <string.h>

#include <iostream>
# include <thread>
# include <string>
#include <unistd.h>
# include <vector>


using namespace std;

vector <thread> threads;

string toString(const char* str) {
  string s;
  int len = strlen(str);
  for(int i = 0; i < len; i++) {
    s.push_back(str[i]);
  }
  return s;
}

void recv_activity(int socket) {
  while(1) {
    string command;
    char buffer[10000];
    bzero(buffer, sizeof(buffer));
    int recv_len = recv(socket, buffer, sizeof(buffer), 0);
    if (recv_len <= 0) {
      exit(0);
    }

    int ptr = 0;
    for(ptr; buffer[ptr] != '$' && buffer[ptr] != '\0'; ptr++)
      command.push_back(buffer[ptr]);
    ptr++;


    string str;
    for (int i = ptr; buffer[i] != '\0'; i++) {
      str.push_back(buffer[i]);
    }

    cout << str << endl;

    if(command == "QUIT") {
      return;
    }
  }
}


void health_check(int socket) {
  while(1) {
    sleep(3);
    string msg = "CHECK";
    send(socket, msg.c_str(), msg.size(), 0);
  }
}

int main(int argc, char *argv[]) {


  int sockfd, portno = 0, n;
  struct sockaddr_in serv_addr;
  struct hostent *server;

  string ip;
  while(*argv[1] != ':') {
    ip.push_back(*argv[1]);
    argv[1]++;
  }
  for(int i = 1; i <= 4; i++) {
    argv[1]++;
    portno = portno * 10 + (*argv[1]) - '0';
  }
  server = gethostbyname(ip.c_str());

  if (server == NULL) {
    fprintf(stderr, "ERROR, no such host\n");
    exit(0);
  }

  bzero((char *) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  bcopy((char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr, server->h_length);
  serv_addr.sin_port = htons(portno);

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    puts("Error on opening socket");
    return 0;
  }

  if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) {
    puts("Error on connection");
    return 0;
  }

  string msg;
  msg = "NEWUSER\n" + toString(argv[3]) + "\n" + toString(argv[2]);

  send(sockfd, msg.c_str(), msg.size(), 0);
  sleep(1);

  thread t1 = thread(recv_activity, sockfd);
  //thread t2 = thread(health_check, sockfd);
  string buffer;

  while(getline(cin, buffer)) {
    if(buffer.empty())
      continue;
    msg.clear();
    bool is_msg = false;
    vector < string > split;
    int ptr = 0;

    /*cout << "Following message from getline:" << endl;
    cout << buffer << endl << endl;*/

    for(ptr; ptr < buffer.size(); ptr) {
      string tmp;
      for(ptr; ptr < buffer.size() && (buffer[ptr] == ' ' || buffer[ptr] == ','); ptr++);
      for(ptr; (is_msg || (buffer[ptr] != ' ' && buffer[ptr] != ',')) && ptr < buffer.size(); ptr++)
        tmp.push_back(buffer[ptr]);
      if(tmp == ":")
        is_msg = true;
      else
        split.push_back(tmp);
    }

    /*if(is_msg) {
      for(int i = 0; i < split.size(); i++) {
        cout << split[i] << endl;
      }
    }*/

    if(split[0] == "/quit") {
      msg = "QUIT";
      send(sockfd, msg.c_str(), msg.size(), 0);
      sleep(1);
      break;
    }

    if(split[0] == "/list") {
      msg = "LIST";
      send(sockfd, msg.c_str(), msg.size(), 0);
      sleep(1);
    }

    if(split[0] == "/join") {
      msg = "JOIN\n" + split[1];
      send(sockfd, msg.c_str(), msg.size(), 0);
      sleep(1);
    }

    if(is_msg) {
      msg = "NEWMSG\n";
      if(split[0] == "All") {
        msg += "ALL\nMSG\n" + split[1];
      }
      else {
        msg += "NALL\n";
        for(int i = 0; i < (int)split.size() - 1; i++) {
          msg += split[i] + '\n';
        }
        msg += "MSG\n" + split.back();
      }
      send(sockfd, msg.c_str(), msg.size(), 0);
      sleep(1);
    }


    buffer.clear();
  }

  exit(0);
  return 0;
}
