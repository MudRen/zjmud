//Room: bingying5.c

inherit ROOM;

void create ()
{
	set ("short", "��Ӫ");
	set ("long", @LONG
������һ���ٽֶ����ı�Ӫ�����뿪����ϳ���ֻ�м���֮ң����
Ӫ�ſ����Ʈ�ż�����Կ�����ʿ�������ڣ����Ҳ�����ɫ��Ѱ����
���ܡ���Ӫ���浽�����йٱ������ػص��߶�����һ���佫����ָ��ʿ
���жӲ�����
LONG);
	 set("exits", ([ /* sizeof() == 1 */
	 	"southeast" : __DIR__"nanan-daokou",
	 ]));
	 set("objects", ([ /* sizeof() == 5 */
	 	__DIR__"npc/fujiang" : 1,
	 	__DIR__"npc/guanbing" : 4,
	 ]));

	 set("outdoors", "changan");
	 setup();
}
