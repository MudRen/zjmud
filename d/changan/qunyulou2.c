//Room: qunyulou2.c

inherit ROOM;

void create()
{
	set("short", "Ⱥ��¥��¥");
	set("long", @LONG
Ⱥ��¥��¥������һ������ߵ�С¥��������ĳһλ�����ͬ����
����֮���������ѱ�Ⱥ��¥���ؽ����¡�ֻ��һ������ȭ���������
Ů�˵Ľ�Ц����ʱ�Ĵӷ����д�����
LONG);
	set("exits", ([ /* sizeof() == 6 */
		"north" : __DIR__"qunyuys1",
		"south" : __DIR__"qunyuys2",
		"west"  : __DIR__"qunyuys3",
		"east"  : __DIR__"qunyuys4",
		"down"  : __DIR__"qunyulou1",
		"up"    : __DIR__"qunyulou3",
	]));

	setup();
}