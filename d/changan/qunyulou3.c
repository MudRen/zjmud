//Room: qunyulou3.c

inherit ROOM;

void create()
{
	set("short", "Ⱥ��¥��¥");
	set("long", @LONG
Ⱥ��¥��¥������һ������ߵ�С¥��������ĳһλ�����ͬ����
����֮���������ѱ�Ⱥ��¥���ؽ����¡�ֻ��һ������ȭ���������
Ů�˵Ľ�Ц����ʱ�Ĵӷ����д�����
LONG);
	set("exits", ([ /* sizeof() == 5 */
		"north" : __DIR__"qunyuys5",
		"south" : __DIR__"qunyuys6",
		"west"  : __DIR__"qunyuys7",
		"east"  : __DIR__"qunyuys8",
		"down"  : __DIR__"qunyulou2",
	]));

	setup();
}