// walker.c

#include <ansi.h>

inherit NPC;

int do_walk();

void create()
{
	set_name("ʰ����", ({ "walker" }));
	set("gender", "����");
	set("age", 53 + random(20));
	set("long", @LONG
����һ��������ʰ���ߣ�����ȥ��ʵ�ͽ��ġ�
LONG );
	set("attitude", "heroism");
       set("icon","05013");
	set("str", 35);
	set("int", 15);
	set("con", 19);
	set("dex", 17);

	set("chat_chance", 30);
	set("chat_msg", ({
		(: do_walk :),
	}));

	setup();
	if (clonep()) keep_heart_beat();

	set("check_time", time());
	carry_object("/clone/cloth/cloth")->wear();
}

int do_walk()
{
	string start_room;
	object room;
	object ob;
	mapping obmap;
	int n;

	if (! environment())
		return 0;

	if (time() - query("check_time") > 900)
	{
		if (! stringp(start_room = query("startroom")) ||
		    ! objectp(room = find_object(start_room)) ||
		    ! mapp(obmap = room->query_temp("objects")) ||
		    member_array(this_object(), values(obmap)) == -1)
		{
			message_vision("$N̾��̾�������ˡ�\n", this_object());
			destruct(this_object());
			return 0;
		}

		set("check_time", time());
	}

	n = 0;
	foreach (ob in all_inventory(environment()))
	{
		if (ob->is_character() ||
		    ob->is_head() ||
		    ob->query("no_get"))
			continue;
		destruct(ob);
		n++;
	}

	if (n == 1)
		message_vision("$Nһ�������ӵ��ϼ���һ��������\n",
			       this_object());
	else
	if (n > 1)
		message_vision("$N�����ڵ��������������˰��죬����һ�Ѷ�����\n",
			       this_object());
			
	random_move();
	return 1;
}

void unconcious()
{
	die();
}
