// Room: /city/kedian3.c

inherit ROOM;

void create()
{
	set("short", "�ͷ�");
	set("long", @LONG
����һ��ܴ�Ŀͷ�������ʮ�ּ�ª����ǽ����ʮ����Сľ����
���ٿ��������¶��ԣ������Ӷ��Ǻ����Ĵ������������Ŵ��ǿյģ�
��������ŵ����˹�ȥ��
LONG );
	set("sleep_room", 1);
	set("no_fight", 1);
	set("hotel",1);
	set("no_clean_up", 0);
	set("item_desc", ([
		"��ľ����" : "��ǽ���ŵ�һЩСľ������Щ�������ڴ�����Ϣ��\n"
		ZJOBACTS"��Ϣ:sleep\n",
	]));
	set("exits", ([
		"out" : __DIR__"kedian2",
	]));
	setup();
}

int valid_leave(object me, string dir)
{
	if ( dir == "out" ) me->delete_temp("rent_paid");

	return ::valid_leave(me, dir);
}

