// shanlu3.c
// Date: Nov.1997 by Venus

inherit BUILD_ROOM;

void create()
{
	set("short", "ɽ·");
	set("long", @LONG
СϪ���ɽ·����Ϫ��һ��Сʯ�š�Ϫ��ũ��С������Ϸ���֡�
�����Ȥ���㲻����Ȼ��̾��һʱ������Զ�ܽ���֮�⡣���ϱ㵽��
�����ã����¾��������á�
LONG);
	set("exits", ([
	    "southup"   : __DIR__"faxisi",
	    "northdown" : __DIR__"fajinsi",
	]));
	set("objects", ([
	    __DIR__"npc/boy" : 3,
	]));
	set("outdoors", "hangzhou");
	set("max_room", 4);
	setup();
}
