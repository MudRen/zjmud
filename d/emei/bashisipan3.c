//Room: bashisipan3.c ��ʮ����
//Date: Oct. 2 1997 by That

inherit ROOM;

void create()
{
      set("short","��ʮ����");
      set("long",@LONG
��ʮ���̣���·���ն��ͣ��ػ����ۣ����˲��ܴ�Ϣ��·���Ǳ��������
��ɼ�֣�·��������׵ľ���Ͽ�ȡ��ɴ���������������µ�ϴ��ء�
LONG);
      set("outdoors", "emei");
      set("exits",([ /* sizeof() == 1 */
	  "northdown"  : __DIR__"bashisipan2",
	  "southeast"  : __DIR__"jieyindian",
	  "northeast"  : __DIR__"lengsl4",
      ]));
      setup();
}
