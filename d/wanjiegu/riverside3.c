// Room: /t/wanjiegu/riverside3.c

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
		"west"    : __DIR__"port",
		"southup" : __DIR__"riverside2",
		"north"   : __DIR__"riverside4",
	]));

	setup();
}
