// bao.c ������

#include <ansi.h>

inherit NPC;
int ask_baowu();

mapping list = ([
	"�����似һ":"/clone/book/wuji1",
	"�����似��":"/clone/book/wuji2",
	"�����伫��":"/clone/book/wuji3",
	"�����伫��":"/clone/book/wuji4",
	"Ǭ����Ų��":"/clone/book/qiankun_book",
	"��������":"/clone/book/six_book",
	"�׽":"/clone/book/yijinjing",
	"����":"/clone/book/lbook4",
	"�����澭���ϲ�":"/clone/book/jiuyin1",
	"�����澭��ȫ":"/d/tulong/obj/zhenjing",
	"ʥ����1":"/clone/book/ling1",
	"ʥ����2":"/clone/book/ling2",
	"ʥ����3":"/clone/book/ling3",
	"������":"/d/tulong/obj/tulongdao",
	"���콣":"/d/tulong/obj/yitianjian",
	"���佣":"/clone/weapon/zhenwu",
]);

void create()
{
	object book;

	set_name("������", ({"bao dating", "dating"}));
	set("gender", "����");
	set("age", 62);
	set("long", "������ȥ��ɫ��Ȼ�����������¾������е����ӡ�\n");
	set("attitude", "peaceful");
	set("shen_type",1);
	set("str", 31);
	set("int", 36);
	set("con", 32);
	set("dex", 29);

	set("qi", 6200);
	set("max_qi", 6200);
	set("jing", 3100);
	set("max_jing", 3100);
	set("neili", 6500);
	set("max_neili", 6500);
	set("jiali", 50);

	set("combat_exp", 2800000);

	set_skill("force", 280);
	set_skill("dodge", 260);
	set_skill("parry", 270);
	set_skill("unarmed", 270);
	set_skill("literate", 120);

	set("title", "������֪");

	set("inquiry", ([
		"��������" : (: ask_baowu :),
	]));

	set_temp("apply/attack", 50);
	set_temp("apply/dodge", 80);
	set_temp("apply/parry", 80);
	set_temp("apply/unarmed_damage", 30);
	set_temp("apply/damage", 30);

	setup();

	carry_object("/clone/misc/cloth")->wear();
}

void init()
{
	add_action("show_baowu","chabw");
}

int ask_baowu()
{
	string str,*items;
	int i;

	object me = this_player();
	str = ZJOBLONG"�������ʲô������������䣺\n"ZJOBACTS2+ZJMENUF(3,3,10,30);
	items = keys(list);
	for(i=0;i<sizeof(items);i++)
	{
		str += items[i]+":chabw "+items[i];
		if(i<(sizeof(items)-1)) str += ZJSEP;
	}
	tell_object(me,str+"\n");
	return 1;
}

int show_baowu(string arg)
{
	object me,ob,*objs;
	int i;
	string str,*names;

	names = ({});
	me = this_player();
	if(!arg||!list[arg])
	{
		tell_object(me,"��Ҫ����ʲô���\n");
		return 1;
	}

	objs = children(list[arg]);

	if(sizeof(objs))
	{
		for(i=0;i<sizeof(objs);i++)
		{
			if(ob=environment(objs[i]))
			{
				if(playerp(ob))
					names += ({ ob->query("name") });
			}
		}
	}
	if(sizeof(names))
	{
		if(sizeof(names)==1)
			say("������˵��Ŀǰ�����г���"+arg+"������У�"+names[0]+"��\n");
		else
			say("������˵��Ŀǰ�����г���"+arg+"������У�"+implode(names,"��")+"��\n");
	}
	else
	{
		say("������˵��Ŀǰ������û����ҳ���"+arg+"��\n");
		return 1;
	}


	return 1;
}

