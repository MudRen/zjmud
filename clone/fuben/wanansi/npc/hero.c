#include <ansi.h>;
inherit NPC;

int dajiu();
string *heros = ({
	"һ������",
	"��������",
	"��������",
	"�Ĳ�����",
	"�������",
	"��������",
	"�߲�����",
	"�˲�����",
	"�Ų�����",
	"ʮ������",
	"ʮһ������",
	"ʮ��������",
	"ʮ��������",
});

void create()
{
	set_name("������", ({"helper man"}));
	set("gender", "����");
	set("age", 45);
	set("long","���Ǳ����������е������������ˡ�\n");
	set("attitude", "peaceful");
 	set("no_death", 1);

	set("str", 38);
	set("int", 20);
	set("con", 20);
	set("dex", 20);
	set("max_qi", 250000);
	set("eff_qi", 250000);
	set("qi", 250000);

	set("neili", 19999);
	set("max_neili", 19999);
	
	set("combat_exp", 600000);

	set_temp("apply/damage", 666);
	set_temp("apply/armor", 300);
	set_temp("apply/speed", 300);

	set("chat_chance", 2);
	set("chat_msg", ({
		 "������������˽е�������λӢ�۸Ͻ����Ⱦ��Ұ�������\n",
	}));

	set("inquiry", ([
		"���" : (: dajiu :),
	]));

	setup();
}

void init()
{
	set("name", heros[environment()->query("sllv")-1]);
}

int dajiu()
{
	if(present("sl dizi",environment()))
	{
		say("������е�����ô�������ҷ������\n");
		return 1;
	}
	say("̫���ˣ��������˴������ˣ�����������ϣ���ˣ�\n");
	if(environment()->query("sllv")>=13)
	{
		say("�㽫���е����ʶ����˳���������\n");
	}
	else
	{
		say("�㽫"+query("name")+"�ͳ����¼�������һ�㴳ȥ������\n");
		environment()->nextlv(3);
	}
	destruct(this_object());
	return 1;
}
