//Room: baodian.c

inherit ROOM;

void create ()
{
	set ("short", "���۱���");
	set ("long", @LONG
���۱����ڣ���ڻԻͣ����������������๲����������ŷ𣬹�
��֮������٤��������ıڻ������۱���Ϊ�����ʵ��м�ɮ�¡�����
�������ڣ����Գ���������������ͬ��������ׯ�����µķ���һ
�㡣
LONG);
	set("exits", 
	([ //sizeof() == 3
		"north" : __DIR__"baoxiangsi",
		"west" : __DIR__"piandian",
		"east" : __DIR__"fangzhangshi",
	]));
	set("objects", 
	([ //sizeof() == 1
		__DIR__"npc/xiangke" : 2,
	]));
	
	setup();
}
