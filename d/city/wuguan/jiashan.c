// jiashan.c
#include <ansi.h>
#include <room.h>
inherit ROOM;
void create()
{
         set("short",HIM"��ɽ"NOR);
         set ("long",@LONG
����������ݵĺ�԰��������ʯ��ᾣ�ƽʱ�������˵���������������
���е�Ҳ�Ѿ���л�ˡ����׵�һ���ɽ����һ����϶��feng����Ŀ��Բ��¸�
���ˡ�����С·����ͨ�����ֵģ�·ǰ����һ�����ӣ�paizi����
LONG
   );
	 set("outdoors","���");
	set("no_fight",1);
	 set("exits",([
		"north" : __DIR__"wxting",
	     "south" : __DIR__"zhulin1",
	 ]));

	 setup();
}
