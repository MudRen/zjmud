// Room: /city/datiepu.c
inherit ROOM;
void create()
{
	set("short", "������");
	set("long", @LONG
����һ�Ҽ�ª�Ĵ����̣����İ���һ����¯��¯��������յ�һƬͨ�죬
��һ�߽�ȥ�͸е�������ȡ�ǽ�Ƕ��������깤��δ�깤�Ĳ˵�����������
����ذ�ס����׵��һλ������ͷ�󺹻�����������ר����־���ڴ�����
LONG );
	set("exits", ([
		"north" : __DIR__"dongdajie2",
	]));
	set("objects", ([
		__DIR__"npc/smith": 1,
	]));
	setup();
}

