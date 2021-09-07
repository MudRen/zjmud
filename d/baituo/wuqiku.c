//wuqiku.c

inherit ROOM;

void create()
{
	set("short", "������");
	set("long",
	     "�����ǡ�����ɽ�����ӵ������⣬������ɽ�����ӿ��Ե���\n"
	 "��ȡ�����õĸ����������������ɵ����ǲ���������ġ�\n"
	);
	set("exits", ([
		"east" : __DIR__"yuanzi",
	]));
	set("objects",([
	     __DIR__"npc/shiwei" : 1,
	     __DIR__"obj/shezhang" : 1,
	     "/clone/weapon/gangzhang" : 2,
	     __DIR__"obj/zheng" : 1,
	]));
	setup();
}

int valid_leave(object me, string dir)
{
	object *inv;

	inv = deep_inventory(me);
	inv = filter_array(inv, (: $1->query("id") == "gangzhang" :));

	if (sizeof(inv) > 1)
		return notify_fail("��λ" + RANK_D->query_respect(me) + "������̰�ģ�����һ�����Ⱦ͹�����\n");

	return ::valid_leave(me, dir);
}
