// Room: practice
// Date: Feb.14 1998 by Java

#include <room.h>
inherit ROOM;

void create()
{
      set("short", "��ݲ�����");
      set("long", @LONG
���������ʯ���������󵶳�����ɳ�����ȵȣ����м���������
���ľ�ˣ�����ݵ����ճ������ĵط���
LONG );

      set("exits", ([ /* sizeof() == 1 */
	  "down"   : __DIR__"wuguan",
      ]));

      set("objects", ([
	  "/clone/npc/tong-ren" : 4,
      ]));

      setup();
}
