// storeroom.c

inherit ROOM;
void init();
int do_open(string);

void create()
{
	set("short", "������");
	set("long", "����һ�������ң������ܲ�͸�硣ֻ�йر��ŵĴ���(door)��\n");
//      case(random(6))
//	{ case 0 :
//	  case 1:
//		set("objects" , ([
//		 "  " :	,
//		   ]));
//		  break;
	set("item_desc" , ([
	 "door" : "һ��ľ�ţ�Ҳ���ܴ򿪡�\n",
	 ]) );
	set("no_clean_up", 0);
	setup();
}

void init()
{
 add_action("do_open","open");
}

int do_open(string arg)
{
  object me=this_player();
  object room;
 if( !arg|| arg!="door")
  return notify_fail("��Ҫ��ʲô��\n");
 if(!( room = find_object(__DIR__"yuanzi")) )
    room = load_object(__DIR__"yuanzi");
 if(!objectp(room))  return notify_fail("ERROR:not found 'yuanzi.c' \n");
 if(room->query_temp("lock")==1)
   return notify_fail("���Ѿ���������ס�ˡ�\n");
 message_vision("$N�����ƿ��ţ����˳�ȥ�����ְ�������������\n",me);
 message("vision", "�������˳��������ְ��������ˡ�\n",room);
 me->move(room);
 return 1;
}
