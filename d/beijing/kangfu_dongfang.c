inherit ROOM;

void create()
{
	set("short", "���᷿");
	set("long", @LONG
�����ǿ�����������ߵ�һ���᷿���ǹ��������Ŀ�������ס�ġ��᷿��
����ż��Ŵ󴲣��������ӡ����й�����ͣ�ʹ�˸���˯�⡣
LONG );
	set("exits", ([
		"west" : __DIR__"kangfu_zoulang2",
	]));

       set("no_fight",1);
       set("no_steal",1);
       set("sleep_room",1);
	set("no_clean_up", 0);
	setup();
}
