// Room: caolian3 ���������
// Date: Sep.30 1997

#include <room.h>

inherit ROOM;

void create()
{
      set("short", "���������");
      set("long", @LONG
��������˴󵶳�����ɳ�����ȵȣ����䵱�����ճ������ĵط���
LONG );

      set("exits", ([ /* sizeof() == 1 */
	    "east"   : __DIR__"caolianfang",
      ]));
      set("objects", ([
	     "/clone/npc/mu-ren" : 4,  //�ĸ�ľ��
      ]));
      set("for_family", "�䵱��");
      setup();
}

