// Room: /d/xingxiu/kedian
inherit ROOM;
void create()
{
	set("short", "�͵�");
	set("long", @LONG
����������˿��֮·�ϵ�һ��С��ջ����ջ��С�����������Ҫ��;���棬
��������Ϣһ�¸���Ŷ��
    ǽ�Ϲ���һ�����ӡ�
LONG );
	set("no_fight", 1);
	set("valid_startroom", 1);
	set("no_sleep_room",1);
	set("item_desc", ([
		"�����ӡ�" : "¥��ס�ޣ�ÿҹ����������\n",
	]));
	set("objects", ([
		__DIR__"npc/shaonv" : 1,
	]));
	set("exits", ([
		"west" : __DIR__"shanjiao",
		"up"    : __DIR__"kedian2",
	]));

	setup();
}

int valid_leave(object me, string dir)
{

	if ( !me->query_temp("rent_paid") && dir == "up" )
	return notify_fail("ά�����Ů��æ����¥��ǰ���������͹٣������ȸ�Ǯ����\n");

	if ( me->query_temp("rent_paid") && dir == "west" )
	return notify_fail("ά�����Ů�ܵ��ű���ס�����������ӣ����᲻ס��������أ�
���˻���ΪС���ź����أ�\n");

	return ::valid_leave(me, dir);
}
