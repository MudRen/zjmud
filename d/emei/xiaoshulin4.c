//Room: xiaoshulin4.c С����
inherit ROOM;
void create()
{
      set("short","С����");
      set("long",@LONG
���Ƕ���ɽ�𶥻��������һƬС���֡������Ƕ�����Ů�����ǵ��޹���
���������º������һ���ˡ�
LONG);
      set("objects", ([
	   __DIR__"npc/xiaosong" : 1,
      ]));
      set("outdoors", "emei");
      set("exits",([ /* sizeof() == 1 */
	  "northwest" : __DIR__"xiaoshulin3", 
	  "north"     : __DIR__"qinggong", 
      ]));
      setup();
}
int valid_leave(object me, string dir)
{
      mapping myfam;
      me = this_player();
      myfam = (mapping)me->query("family");
      if ((!myfam || (myfam["family_name"] != "������")) && (dir == "north"))
	  return notify_fail("��ô�ĵ��ӣ��봳����Ů���ӵ��޹���\n");
      else  return 1;
}
