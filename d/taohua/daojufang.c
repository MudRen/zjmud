inherit ROOM;

void create()
{
	set("short", "���߷�");
	set("long", @LONG
����һ����߷�������һЩ�һ������ǳ��õĶ�������������
�����ģ���������һ�Ű߲�������һ�ѿ����Σ����ǰ��컹����С��
�ơ����Ϳ������������ʹ�������㣬��Ȼ�ڲ����ԣ����㻹������
�㷡�
LONG );
	set("exits", ([
		"west" : __DIR__"dating",
		"up"   : __DIR__"shufang",
	]));
	set("objects", ([
		__DIR__"npc/yapu"  : 2,
		__DIR__"obj/xiang" : 1,
		__DIR__"obj/zhuxiao" : 1,
	]) );
	setup();
}
