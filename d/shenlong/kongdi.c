inherit ROOM;
 
void create()
{
	set("short", "�յ�");
	set("long",@LONG
����һƬ�յأ����ܶ�����ʯ���Ӳݴ�����������һ��С�ݡ���
��������Ĺ�ľ�֡�������һ�������Ĵ����������һƬ��ƺ��
LONG);
	set("exits", ([
		"west" : __DIR__"jingji/enter",
		"east" : __DIR__"road",
		"north" : __DIR__"caodi",
		"south" : __DIR__"lin2",
	]) );

	set("objects", ([
		CLASS_D("shenlong")+"/xu": 1,
		__DIR__"npc/dizi": random(3),
	]) );
	set("outdoors", "shenlong");
	setup();
}


