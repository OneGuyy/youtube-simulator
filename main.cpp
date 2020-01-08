#include <iostream>
#include <string>
#include <vector>
//#include <fstream>
#include <random>
#include <chrono>
#include <cmath>

//STRUCT

//Statistics Struct
struct statistics{
	float views = 0;
	int subs = 0;
	int likes = 0;
	int dislikes = 0;
	float money = 0;
};

//Video Struct with statistics
struct video{
	std::string name;
	std::string genre;
	int releaseDate;
    statistics stats;
};

//Channel Struct with a vector of video
struct channel{
	std::string name;
	statistics stats;
	std::vector<video> listVideos;
};

//Struct player who have a youtube channel.
struct player{
		float money{100.00};
		int tiredness{100};
		int hunger{100};
		channel youtube;
};


//FONCTIONS
//Void fonctions :

//Rename your channel
void rename(channel& c){
	std::cout << "New channel name : ";
	while(!(std::getline(std::cin, c.name))){
		std::cout << "ERROR, enter a valid value !" << std::endl;
		std::cin.clear();
		std::cin.ignore(255, '\n');
	}
}

//Show your channel stats
void channelStats(const channel& c){
	auto const tabSize{c.listVideos.size()};
	std::cout << "Channel Name\t\t:\t" << c.name << std::endl;
	std::cout << "Number of Videos\t:\t" << tabSize << std::endl;
	std::cout << "Actual Subscibers\t:\t" << c.stats.subs << std::endl;
	std::cout << "Total Views\t\t:\t" << static_cast<int>(c.stats.views) << std::endl;
	if(tabSize != 0){
	std::cout << "Views per Video\t\t:\t" << static_cast<int>(c.stats.views/tabSize) << std::endl;
	}
	std::cout << std::defaultfloat;
	std::cout << "Total Money\t\t:\t" << round(c.stats.money*100)/100 << std::endl;
	std::cout << std::fixed;
}



//Display all the functions and what they do
void help(){
	std::cout << "!HELP\t\t->\tView all functions." << std::endl;
	std::cout << "!VIDEO\t\t->\tCreate a new Video." << std::endl;
	std::cout << "!STATS\t\t->\tView all the statistics of your channel." << std::endl;
	std::cout << "!EAT\t\t->\tEat to decrease hunger (it costs 20$ for 40 points)." << std::endl;
	std::cout << "!WORK\t\t->\tWork to win money (If you work too much, you'll get much money but you'll be tired !)" << std::endl;
	std::cout << "!SLEEP\t\t->\tSleep to don't be tired anymore (it en/ds the day !)" << std::endl;
	//std::cout << "!BUY\t\t->\tBuy new stuff to increase your video quality !" << std::endl;
	std::cout << "!MONEY\t\t->\tShow you how much money you have." << std::endl;
	std::cout << "!LISTVIDEOS\t->\tShow you all of your videos with their statistics." << std::endl;
	std::cout << "!ENERGY\t\t->\tShow you how much tired and hungry you are." << std::endl;
	std::cout << "!RENAME\t\t->\tRename the name of your channel." << std::endl;
	std::cout << "!END\t\t->\tClose the Game ! (Save function isn't available now !)" << std::endl;
}

//Eat costs 20$. Only works if you have more than 20$ and if you are hungry
void eat(player& p){
	if(p.money<20){
		std::cout << "You don't have enought money..." << std::endl;
	}
	else if(p.hunger==100){
		std::cout << "You're not hungry..." << std::endl;
	}
	else{
		p.hunger+=40;
		if(p.hunger>100){
			p.hunger=100;
		}
		p.money-=20;
	}
}

//Display all the videos you've done and their statistics
void allVideos(player& p){
	for(auto const video : p.youtube.listVideos){
        std::cout << sttd::endl;
		std::cout << "Title : " << video.name << "\t\t|\t" << "Genre\t\t: " << video.genre << std::endl;
		std::cout << "Views : " << video.stats.views << "\t\t|\t" << "Subscibers\t: " << video.stats.subs << std::endl;
		std::cout << "Money : " << round(video.stats.money*100)/100 << "\t\t|\t" << "Release Date\t: Day " << video.releaseDate << std::endl;
	}
    std::cout << std::endl;
}

//Display tiredness and hunger
void energy(const player& p){
    std::cout << "Tiredness\t:\t" << p.tiredness << std::endl;
    std::cout << "Hunger\t\t:\t" << p.hunger << std::endl;
}

//Work to win money but you'll be tired after !
void work(player& p){
	int wanted{}; int provTiredness{}; int provHunger{};
	std::cout << "How much money you want ?" << std::endl;
	std::cout << "Money : ";
	while(!(std::cin >> wanted) || wanted < 0){
		std::cout << "Error, please type a correct value." << std::endl;
		std::cin.clear();
		std::cin.ignore(255, '\n');
		std::cout << "Money : ";
	}
	std::cin.ignore(255, '\n');
	provHunger = wanted*0.5;
	provTiredness = wanted*0.8;
	std::cout << "It will cost you " << provTiredness << " tiredness points and " << provHunger << " hunger points." << std::endl;
	if(provTiredness >= p.hunger){
		std::cout << "You'll be too much tired !!" << std::endl;
	}
	else if(provHunger >= p.hunger){
        std::cout << "You'll be too much hungry !" << std::endl;
	}
	else{
		p.money += wanted;
		p.tiredness -= provTiredness;
		p.hunger -= provHunger;
		std::cout << "You have won " << wanted << " dollars." << std::endl;
	}
}

//Show how much money you've got
void displayMoney(player& p){
	std::cout << std::defaultfloat;
	std::cout << "Money : " << round(p.money*100)/100 << std::endl;
	std::cout << "Money for 1000 views : " << round(p.youtube.stats.money/((p.youtube.stats.money/1000)*100))/100 << std::endl;
	std::cout << std::fixed;
}

//Video Fonction :
video newVideo(player& p, int day){
	video v;
	std::default_random_engine re(std::chrono::system_clock::now().time_since_epoch().count());
	//We define the cpm
	float cpm;
	std::uniform_int_distribution<int> firstCPM{6, 11};
	cpm = firstCPM(re);
	cpm = cpm/10;

	//BUZZ !
	std::uniform_int_distribution<int> buzz{1,100};


	//Release date of the video
	v.releaseDate = day;

	//Here, you create the video with his name and his genre
	std::cout << "Name of the Video : ";
    while(!(std::getline(std::cin, v.name))){
        std::cout << "ERROR, enter a valid value !" << std::endl;
        std::cin.clear();
        std::cin.ignore(255, '\n');
    }
	std::cout << "Genre of the Video : ";
    while(!(std::getline(std::cin, v.genre))){
        std::cout << "ERROR, enter a valid value !" << std::endl;
        std::cin.clear();
        std::cin.ignore(255, '\n');
    }

    //We determinate how much views and subs video will do
    //If you got 0 subs
    if(p.youtube.stats.subs == 0){
   		std::uniform_int_distribution<int> distrib{10, 150};
   		v.stats.views = distrib(re);
   		p.youtube.stats.views += v.stats.views;
   		std::cout << "Views : " << static_cast<int>(round(v.stats.views)) << "|";
   		v.stats.subs = v.stats.views/20;
   		p.youtube.stats.subs += v.stats.subs;
   		std::cout << "Subs : " << v.stats.subs << "|";
		v.stats.money += (v.stats.views/1000)*cpm;
		p.money += v.stats.money;
		p.youtube.stats.money += v.stats.money;
		std::cout << std::defaultfloat;
   		std::cout << "Money : " << round(v.stats.money*100)/100 << "|" << std::endl;
	}
	//If you got between 1 and 100 subs
	else if(p.youtube.stats.subs <= 100){
		std::uniform_int_distribution<int> distrib{p.youtube.stats.subs, p.youtube.stats.subs+150};
		v.stats.views = distrib(re);
		p.youtube.stats.views += v.stats.views;
		std::cout << "Views : " << static_cast<int>(round(v.stats.views)) << "|";
		v.stats.subs = p.youtube.stats.views/50;
		p.youtube.stats.subs += v.stats.subs;
		std::cout << "Subs : " << v.stats.subs << "|";
		v.stats.money += (v.stats.views/1000)*cpm;
		p.money += v.stats.money;
		p.youtube.stats.money += v.stats.money;
		std::cout << std::defaultfloat;
		std::cout << "Money : " << round(v.stats.money*100)/100 << "|" << std::endl;
	}
	//If you got more than 100 subs
	else{
		std::uniform_int_distribution<int> distrib{1/5*p.youtube.stats.subs, 2*p.youtube.stats.subs};
		v.stats.views = distrib(re);
		p.youtube.stats.views += v.stats.views;
		std::cout << "Views : " << static_cast<int>(round(v.stats.views)) << "|";
		v.stats.subs = p.youtube.stats.views/50;
		p.youtube.stats.subs += v.stats.subs;
		std::cout << "Subs : " << v.stats.subs << "|";
		v.stats.money += (v.stats.views/1000)*cpm;
		p.money += v.stats.money;
		p.youtube.stats.money += v.stats.money;
		std::cout << std::defaultfloat;
		std::cout << "Money : " << round(v.stats.money*100)/100 << "|" << std::endl;
	}
	std::cout << "You lost 20 hunger points and 35 tiredness points." << std::endl;
	p.hunger -= 20; p.tiredness -= 35;
	std::cout << std::fixed;
	return v;
}

//MAIN

int main(){
	std::cout << std::fixed;
	//We create files to save the game
	//std::string const fileEmplacement{"mainGame.txt"};
	//std::ifstream saveFile {fileEmplacement};

	//Here, we verify if file can be open, if it can, we can start the game
	//if(saveFile){
		player user;
		std::cout << "Channel name : ";
		while(!(std::getline(std::cin, user.youtube.name))){
			std::cout << "ERROR, enter a valid value !" << std::endl;
			std::cin.clear();
			std::cin.ignore(255, '\n');
		}

		//Introduction
		std::cout << "Hello " << user.youtube.name << " and welcome to YouToube life 0.1 !\nHere, you can see YouToubers !\nHave fun on YouToube life !" << std::endl;

        std::cout << std::endl;
		//Game

        //Random engine :

		//All variables of the game
		int day{0};
		std::string function{""};
		std::cout << "To know all the functions, type !HELP" << std::endl;

        std::cout << std::endl;

        //The game day by day
		while(true){
			day++;
			std::cout << "Day " << day << std::endl;
			do{
			std::cout << "What to do : ";
			std::getline(std::cin, function);
			if(function == "!HELP"){
				help();
			}
			else if(function == "!EAT"){
				eat(user);
			}
			else if(function == "!STATS"){
				channelStats(user.youtube);
			}
			else if(function == "!ENERGY"){
				energy(user);
			}
			else if(function == "!WORK"){
				work(user);
			}
			else if(function == "!RENAME"){
				rename(user.youtube);
			}
			else if(function == "!MONEY"){
				displayMoney(user);
			}
			else if(function == "!VIDEO"){
				if(user.hunger<20){
						std::cout << "You are too much hungry !" << std::endl;
				}
				else if(user.tiredness<35){
						std::cout << "You are too much tired !" << std::endl;
				}
				else{
					user.youtube.listVideos.push_back(newVideo(user, day));
				}
			}
			else if(function == "!LISTVIDEOS"){
				allVideos(user);
			}
			else if(function != "!SLEEP" && function != "!END"){
				std::cout << "Error, unknown function." << std::endl;
			}
			}
			while(function != "!SLEEP" && function != "!END");
			if(function == "!END"){
				return 0;
			}
			std::cout << std::endl;
			function = "";
            user.tiredness = 100;
		}
	//}

	//else{
	//	std::cout << "ERROR ! File can't be open !" << std::endl;
	//}

    return 0;
}
