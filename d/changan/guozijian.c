//Room: guozijian.c

inherit ROOM;

void create ()
{
	set ("short", "���Ӽ�");
	set ("long", @LONG
���Ӽ��ǳ�͢�����˲ŵĵط����߸ߵ͵͵������������š�������
��ʱ���Կ�������������ѧ��ģ�����˴���������ʲô���⣬����һЩ
������������üͷ�Ҵҵ��߹���������˼����ʲô���⡣
LONG);
	//set("item_desc", ([" *** " : " *** ", ]));

	set("exits", 
	([ //sizeof() == 1
		"south" : __DIR__"baihu3",
	]));
	set("objects", 
	([ //sizeof() == 1
		__DIR__"npc/xueshi" : 1,
	]));
	      
	setup();
}
