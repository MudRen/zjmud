// Room: path2.c
inherit ROOM;
string look_gaoshi();
void create()
{
	set("short", "佻�Ϫ");
	set("long", @LONG
ϪԴת��������ˮ���������������ǰ��վ�ڲ����ձ�ǰ������
佻�Ϫ���������Ư׹����Ů���佻�ʱ�ڣ�����һ����ζ�����߾�
�ǡ���������լ���ٻ�̶��ׯ���ĶŸ������ˡ�
LONG );
	set("outdoors", "chengdu");
	set("exits", ([
		"north"  : __DIR__"caotang",
		"south"  : __DIR__"path1",
	]));
	set("no_clean_up", 0);
	setup();
}
