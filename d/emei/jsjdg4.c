//Room: jsjdg4.c ��ʮ�ŵ���
//Date: Oct. 2 1997 by That

inherit ROOM;

void create()
{
      set("short","��ʮ�ŵ���");
      set("long",@LONG
���������ġ���ʮ�ŵ��ա�����·����������ǧ�۰ٻء���˵��ȥ���и�
������ķ�ɮ���ˣ���һ������·�������������������ǵ�֪�˴��о�����û
�󣬱���Ҳ���˸�������Ĳ�ľ�����ԡ����ӡ���֮���ɴ˶�����ǧ���֣���
����϶���
LONG);
      set("outdoors", "emei");
      set("exits",([ /* sizeof() == 1 */
	  "eastdown"  : __DIR__"jsjdg3",
	  "southwest" : __DIR__"jldongkou",
      ]));
      setup();
}
