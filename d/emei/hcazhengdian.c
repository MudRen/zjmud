//Room: hcazhengdian.c ����������
//Date: Oct. 2 1997 by That

inherit ROOM;

void create()
{
      set("short","����������");
      set("long",@LONG
�����Ƕ���ɽ�𶥻����ֵ���������ֹ�ģ��󣬵�����ש�̵أ��м�
�������������������������ǰ����һ��ľ���������������Թ�ߵ�ݡ�
�Դ����Ҹ���һ����ǽӴ���͵ĵط���������ͨ��һ����㳡��ֻ�ж�
�ҵ��Ӳ��ܹ�ȥ��
LONG);
      set("objects", ([
	   CLASS_D("emei") + "/xin" : 1,
	   __DIR__"npc/guest" : 1,
      ]));
      set("exits",([ /* sizeof() == 1 */
	  "out"    : __DIR__"huacangan",
	  "east"   : __DIR__"hcaeast", 
	  "west"   : __DIR__"hcawest", 
	  "south"  : __DIR__"hcaguangchang", 
      ]));
	set("valid_startroom", 1);
      setup();
}

int valid_leave(object me, string dir)
{
	object ob;

	if (dir != "out" &&
	    objectp(ob = present("jingxin shitai", this_object())))
		return ob->permit_pass(me, dir);
	return ::valid_leave(me, dir);
}

