// shanlu1.c ɽ·
// By Lgg,1998.10

inherit ROOM;

void create()
{
	set("short", "ɽ·");
	set("long", @LONG
���书���ų�����·�Ʊ伱�ˣ�����һ����ʯ���̳ɵ�ɽ·��·
���Թ�ͺͺ�ģ�û��ʲô��ľ��ȫ��һ���Ĵ�ʯͷ������·����ͨ
��ǰ�������ɽ�ϡ�������һ��С��ׯ������������ȽȽ�Ĵ��̡�
LONG
	);
	set("outdoors", "wugong");
	set("exits", ([
		"eastup" : __DIR__"shanlu2",
		"northup" : __DIR__"xiaocun",
		"southwest" : __DIR__"ximen",
	]));
	setup();
}
