// by ranger_游侠
// heishi.c

inherit ROOM;

void create()
{
	set("short", "黑市");
	set("long", "这里是黑市，物品交易的场所。");
	set("exits", ([
		"northwest":__DIR__"guangchang",
	]));
	set("objects", ([
	]));
	set("action_list", ([
		"寄售物品" : "jishou",
		"物品列表" : "jylist",
	]));
	set("no_fight","1");
	set("no_steal", "1");
	set("no_sleep_room", "1");
	setup();
}

void init()
{
	add_action("do_stock", "jishou");
	add_action("do_buy", "jybuy");
	add_action("do_list", "jylist");
	add_action("do_cha", "jychakan");
	add_action("do_unstock", "quhui");
}

int do_stock(string arg)
{
	tell_object(this_player(),SALE_D->do_stock(this_player(),arg)+"\n");
	return 1;
}

int do_buy(string arg)
{
	tell_object(this_player(),SALE_D->do_buy(this_player(),arg)+"\n");
	return 1;
}

int do_cha(string arg)
{
	tell_object(this_player(),SALE_D->do_cha(this_player(),arg)+"\n");
	return 1;
}

int do_list(string arg)
{
//	return notify_fail(OKSAY"集市暂时关闭！\n");
	if(!arg)
		arg = "全部 1";
	tell_object(this_player(),SALE_D->do_list(this_player(),arg)+"\n");
	return 1;
}

int do_unstock(string arg)
{
	tell_object(this_player(),SALE_D->do_unstock(this_player(),arg)+"\n");
	return 1;
}
