// Room: /t/wanjiegu/riverside4.c

inherit ROOM;

void create()
{
	set("short", "����С·");
	set("long", @LONG
�������׽��ߵ�һ��С·����ˮ���ϣ������汼�ڶ���������
�ϲ�ʱ���������ĺ��������뽭��ĺ�Х���γ�һ�����˵Ľ����֡�
LONG
	);
	set("outdoors", "wanjiegu");
	set("exits", ([ /* sizeof() == 2 */
	    "northwest" : __DIR__"wlshan",
	    "south"     : __DIR__"riverside3",
	]));

	setup();
}
