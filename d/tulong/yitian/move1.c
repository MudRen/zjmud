inherit ROOM;

void create()
{
	set("short", "Ԫ�󶼳�����");
	set("long", @LONG
������Ԫ�󶼳ǵ����ģ�Ҳ���Ǻ��������ǵ�ǰ����ɫ�ĳ�ǽ������ׯ
������֮�У�ԶԶ��ȥ����¥�������淢�Ե���ΰ�ߴ�һ�����Ǻ��ƳǶ�����
LONG );
	set("no_fight", 1);
	set("no_steal", 1);
	set("no_beg",1);

	set("objects", ([
		"/d/beijing/npc/maiyi1" : 1,
		"/d/beijing/npc/old2" : 1,
		"/d/beijing/npc/kid1" : 1,
	]));
	set("outdoors", "beijing");
	setup();
}


