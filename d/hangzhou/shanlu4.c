// shanlu4.c
// Date: Nov.1997 by Venus

inherit BUILD_ROOM;

void create()
{
	set("short", "ɽ·");
	set("long", @LONG
�����������С·�ϣ�������;ɽ����Ӱ��������У���ʯ�߲���
�����е��ػ��泩�����볤�Ӵ˵ء����ϱ㵽�������ã����¾͵���
������
LONG);
	set("exits", ([
	    "westup"   : __DIR__"faxisi",
	    "eastdown" : __DIR__"shanlu5",
	]));
	set("outdoors", "hangzhou");
	set("max_room", 4);
	setup();
}
