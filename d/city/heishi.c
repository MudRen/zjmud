// by ranger_����
// heishi.c

inherit ROOM;

void create()
{
	set("short", "����");
	set("long", "�����Ǻ��У���Ʒ���׵ĳ�����");
	set("exits", ([
		"northwest":__DIR__"guangchang",
	]));
	set("objects", ([
	]));
	set("action_list", ([
		"������Ʒ" : "jishou",
		"��Ʒ�б�" : "jylist",
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
//	return notify_fail(OKSAY"������ʱ�رգ�\n");
	if(!arg)
		arg = "ȫ�� 1";
	tell_object(this_player(),SALE_D->do_list(this_player(),arg)+"\n");
	return 1;
}

int do_unstock(string arg)
{
	tell_object(this_player(),SALE_D->do_unstock(this_player(),arg)+"\n");
	return 1;
}
