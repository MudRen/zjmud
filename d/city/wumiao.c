// Room: /city/wumiao.c
// YZC 1995/12/04 

#include <room.h>

inherit ROOM;

int is_chat_room() { return 1; }

void create()
{
	set("short", "武庙");
	set("long", @LONG
这里是岳王庙的正殿，内有岳飞像，像上方悬挂岳飞手书“还我河山”的
横匾。殿两侧壁上嵌着“尽忠报国”四个大字。武人到此，都放下武器，毕恭
毕敬地上香礼拜。旁边似乎有一道侧门。
LONG );
	set("no_fight", "1");
	set("no_steal", "1");
	set("no_sleep_room", "1");

	set("valid_startroom","1");
	set("objects", ([
		__DIR__"obj/box" : 1,
	]));

	set("action_list", ([
		"每日签到" : "day_sign",
	]));

	set("exits", ([
		"east" : __DIR__"beidajie2",
		"up"   : __DIR__"wumiao2",
		"northwest": "/d/wizard/guest_room",
	]));
	create_door("northwest", "竹门", "southeast", DOOR_CLOSED);
	setup();
}

void init()
{
	add_action("do_sign","day_sign");
}

int do_sign(string arg)
{
	object ob,me;
	string file;
	int vlv,last,times,pot,sign;
	mapping gifts;

	me = this_player();

	last = me->query("last_day_sign");
	if(localtime(time())[3] == localtime(last)[3])
		return notify_fail("你今天已签过到了。\n");

	me->set("last_day_sign",time());
	me->add("potential",5000);
	me->add("combat_exp",5000);
	tell_object(me,"你获得 5000 点经验和潜能。\n");
	ob = new("/clone/shizhe/dan_chongmai1");
	tell_object(me,"你获得 "+ob->short()+"。\n");
	ob->move(me);
	GIFT_D->check_gift(me);

	return 1;
}

int valid_leave(object me, string dir)
{
	if (dir == "northwest" && ! userp(me) && ! me->is_chatter())
		return 0;
	return ::valid_leave(me, dir);
}

