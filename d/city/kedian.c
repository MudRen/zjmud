// Room: /city/kedian.c

#include <room.h>

inherit CREATE_CHAT_ROOM;

void create()
{
	set("short", "宝昌客栈");
	set("long", @LONG
这里是生意兴隆的宝昌客栈，附近的外地游客多选择在此落脚。一个年轻
的店小二里里外外忙得团团转，接待着南腔北调的客人。客店的主人从不露面，他究竟是谁，江湖中流传着各种各样的猜测。
LONG );
	set("no_fight", 1);
	set("valid_startroom", 1);
	set("no_sleep_room",1);
	set("item_desc", ([
		"【牌子】" : "楼上雅房，每夜十两白银，如果你想上二楼休息，你需要交给小二足够的银子。\n"
		ZJOBACTS2+ZJMENUF(2,3,9,28)"付钱住店:give 10 silver to xiao er\n",
	]));
	set("objects", ([
		__DIR__"npc/xiaoer" : 1,
		"/adm/npc/shizhe" : 1,
	  
	]));
	set("action_list", ([
		"存盘":"save",
	]));
	set("exits", ([
		"west" : __DIR__"beidajie1",
		"up"   : __DIR__"kedian2",
		"north": __DIR__"liaotian",
	]));

	setup();
}

void init()
{
	add_all_action();
}

int valid_leave(object me, string dir)
{

	if (! me->query_temp("rent_paid") && dir == "up")
		return notify_fail("店小二一下挡在楼梯前，白眼一翻：怎麽着，想白住啊！\n");

	if (me->query_temp("rent_paid") && dir == "west")
		return notify_fail("店小二跑到门边拦住：客官已经付了银子，怎麽不住店就走了呢！旁人还以为小店伺候不周呢！\n");

	return ::valid_leave(me, dir);
}
