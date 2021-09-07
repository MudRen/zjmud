//fujiang.c

inherit NPC;

string weapon_file, skill, special_skill;
string *first_name = ({ "��","Ǯ","��","��","��","��","֣","��","��","��","ף",
			"κ","��","��","��","��", "��","��","��","��","ŷ��",
			"˾��","Ľ��","���" });
string *name_words = ({ "˳","��","��","��","��","��","��","��","־","��",
	"Т","��","��","��","��","��","��","ʢ","ʤ","��","��","��","ͬ","��",
	"��","��","��","¡","��","��","��","��","��","˼","��","��","��","ƽ",
	"��","��","ά","��","��","Ϫ","��","��","ɽ","��","��","Ȫ","��","ѷ", });

void determine_data()
{
	switch(random(5))
	{
	case 0:
		weapon_file="changjian";
		skill="sword";
		break;
	case 1:
		weapon_file="gangdao";
		skill="blade";
		break;
	case 2:
		weapon_file="gangzhang";
		skill="staff";
		break;
	case 3:
		weapon_file="changbian";
		skill="whip";
		break;
	case 4:
		weapon_file="axe";
		skill="axe";
		break;
	}
}

void create()
{
	string name;
	name = first_name[random(sizeof(first_name))];
	name += name_words[random(sizeof(name_words))];
	if (random(10) > 2) name += name_words[random(sizeof(name_words))];
	set_name(name, ({"fu jiang","fu","jiang", "general", "fujiang"}));
	set ("long", @LONG
һ��ս�����۵ĸ��������̫ƽ�ˣ������������Է��߽��б䡣
LONG);
	determine_data();
	set("title", "����");
	set("gender", "����");
	set("age", 20 + random(30));
	set("combat_exp", 300000 + random(100000));
	set_skill(skill, 120);
	set_skill("dodge", 120);
	set_skill("parry", 120);
	set_skill("unarmed", 120);
	set_skill("force", 120);
	set("max_qi", 700);
	set("max_jing", 700);
	set("max_neli", 800);
	set("force", 1000);
	set("jiali", 25);

	setup();
	carry_object(__DIR__"obj/" + weapon_file)->wield();
	carry_object(__DIR__"obj/zhanjia")->wear();
}
