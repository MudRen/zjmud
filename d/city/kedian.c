// Room: /city/kedian.c

#include <room.h>

inherit CREATE_CHAT_ROOM;

void create()
{
	set("short", "������ջ");
	set("long", @LONG
������������¡�ı�����ջ������������οͶ�ѡ���ڴ���š�һ������
�ĵ�С����������æ������ת���Ӵ�����ǻ�����Ŀ��ˡ��͵�����˴Ӳ�¶�棬��������˭�������������Ÿ��ָ����Ĳ²⡣
LONG );
	set("no_fight", 1);
	set("valid_startroom", 1);
	set("no_sleep_room",1);
	set("item_desc", ([
		"�����ӡ�" : "¥���ŷ���ÿҹʮ����������������϶�¥��Ϣ������Ҫ����С���㹻�����ӡ�\n"
		ZJOBACTS2+ZJMENUF(2,3,9,28)"��Ǯס��:give 10 silver to xiao er\n",
	]));
	set("objects", ([
		__DIR__"npc/xiaoer" : 1,
		"/adm/npc/shizhe" : 1,
	  
	]));
	set("action_list", ([
		"����":"save",
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
		return notify_fail("��С��һ�µ���¥��ǰ������һ���������ţ����ס����\n");

	if (me->query_temp("rent_paid") && dir == "west")
		return notify_fail("��С���ܵ��ű���ס���͹��Ѿ��������ӣ����᲻ס��������أ����˻���ΪС���ź����أ�\n");

	return ::valid_leave(me, dir);
}
