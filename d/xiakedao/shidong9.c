// shidong9.c ʯ��

inherit ROOM;

void create()
{
	set("short", "ʯ��");
	set("long", @LONG
����һ����С��ʯ�������ߵ��ź��򣬹����䰵��ȴҲ�ܱ��
�������������ţ�����Լ������ǰ����һ����Ӱ��ֻ��������
ɫ����������ǰ����һ��Ψ�Ҷ�������ӡ�
LONG );
	set("exits", ([
		"west" : __DIR__"shidong10",
		"east" : __DIR__"yadi",
	]));

	setup();
}
