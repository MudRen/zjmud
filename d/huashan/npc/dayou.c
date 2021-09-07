// dayou.c 

inherit NPC;
inherit F_GUARDER;

void create()
{
	set_name("½����", ({ "lu dayou", "lu", "dayou" }));
	set("nickname", "�����");
	set("long", 
"½������ĺ��ݣ��ֳ��ļ�������ģ���������ò�������\n"
"ͬ�������е������ǻ�ɽ������һ���еĺ��֡���������һֻС\n"
"�һ���۾��Ĵ���ת��\n");
	set("gender", "����");
	set("age", 26);
	set("attitude", "peaceful");
	set("shen_type", 1);
	set("str", 23);
	set("int", 23);
	set("con", 24);
	set("dex", 28);
	
	set("max_qi", 800);
	set("max_jing", 600);
	set("neili", 800);
	set("max_neili", 800);
	set("jiali", 20);
	set("combat_exp", 50000);
	set("score", 5000);

	set_skill("force", 40);
	set_skill("huashan-xinfa", 40);
	set_skill("dodge", 60);
	set_skill("parry", 50);
	set_skill("sword", 60);
	set_skill("huashan-sword", 60);

	map_skill("force", "huashan-xinfa");
	map_skill("parry", "huashan-sword");
	map_skill("sword", "huashan-sword");

	set("coagents", ({
		([ "startroom" : "/d/huashan/qunxianguan",
		   "id"	: "yue buqun" ]),
	}));

	create_family("��ɽ��", 14, "����");

	setup();
	carry_object("/clone/weapon/changjian")->wield();
}
