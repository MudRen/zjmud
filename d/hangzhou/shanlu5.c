// shanlu5.c
// Date: Nov.1997 by Venus

inherit BUILD_ROOM;

void create()
{
	set("short", "ɽ·");
	set("long", @LONG
����С·�ϣ�ֻ����ɽ��Ұ���������͵Ĳ��ũ����Ů���ڻ�
Ц���вɲ裬���˲��ɵþ���������ɱ��ֻ��þӴ˵ء���ɽ·����
�������ߣ����߾�����������������һ����·��
LONG);
	set("exits", ([
		"westup"   : __DIR__"shanlu4",
		"northeast": __DIR__"tulu1",
		"north"    : __DIR__"longjing",
		"east"     : __DIR__"yanxiadong",
	]));
	set("objects", ([
		__DIR__"npc/caichanu" :2,
	]));
	set("outdoors", "hangzhou");
	set("max_room", 4);
	setup();
}
