//Room: ssyb.c �����±�
//Date: Oct. 21 1997 by That

inherit ROOM;
void create()
{
      set("short","�����±�");
      set("long",@LONG
�������ε��±ڡ�̧ͷ������΢����⡣���泱ʪ���ѷ���΢��ˮ��
�������������ǵĳ�ˮ�����ܵľ��ﶼ�����塣�򶫾�������ʱ��ˮ̶��
LONG);
      set("outdoors","emei");
      set("objects", ([
	  __DIR__"npc/frog" : 1,
      ]) );
      set("exits",([ /* sizeof() == 1 */
	  "east"  : __DIR__"st8", 
      ]));
      set("no_clean_up", 0);
      set("no_fight",1);
      setup();
}

void init()
{
    add_action("do_climb","climb");
}

int do_climb()
{
    object me;
    me = this_player();
    message("vision", me->name()+"ʹ������ȥ�����˾�ţ����֮����\n", environment(me), ({me}) );
    me->move(__DIR__"gudelin1");
    message("vision", me->name()+"���˾�ţ����֮������������ط���ȴ��֪�������\n", environment(me), ({me}) );
    return 1;
}
