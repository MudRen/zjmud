// bao.c 包打听

#include <ansi.h>

inherit NPC;
int ask_baowu();

mapping list = ([
	"少林武技一":"/clone/book/wuji1",
	"少林武技二":"/clone/book/wuji2",
	"少林武极三":"/clone/book/wuji3",
	"少林武极四":"/clone/book/wuji4",
	"乾坤大挪移":"/clone/book/qiankun_book",
	"六脉神剑谱":"/clone/book/six_book",
	"易筋经":"/clone/book/yijinjing",
	"论语":"/clone/book/lbook4",
	"九阴真经·上册":"/clone/book/jiuyin1",
	"九阴真经·全":"/d/tulong/obj/zhenjing",
	"圣火令1":"/clone/book/ling1",
	"圣火令2":"/clone/book/ling2",
	"圣火令3":"/clone/book/ling3",
	"屠龙刀":"/d/tulong/obj/tulongdao",
	"倚天剑":"/d/tulong/obj/yitianjian",
	"真武剑":"/clone/weapon/zhenwu",
]);

void create()
{
	object book;

	set_name("包打听", ({"bao dating", "dating"}));
	set("gender", "男性");
	set("age", 62);
	set("long", "他看上去深色淡然，好像天下事尽在心中的样子。\n");
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

	set("title", "无所不知");

	set("inquiry", ([
		"江湖宝物" : (: ask_baowu :),
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
	str = ZJOBLONG"你想打听什么江湖宝物的下落：\n"ZJOBACTS2+ZJMENUF(3,3,10,30);
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
		tell_object(me,"你要打听什么宝物？\n");
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
			say("包打听说：目前江湖中持有"+arg+"的玩家有："+names[0]+"。\n");
		else
			say("包打听说：目前江湖中持有"+arg+"的玩家有："+implode(names,"、")+"。\n");
	}
	else
	{
		say("包打听说：目前江湖中没有玩家持有"+arg+"！\n");
		return 1;
	}


	return 1;
}

