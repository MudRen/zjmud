// xilingqiao.c  ������
inherit ROOM; 
void create() 
{ 
	set("short", "������"); 
	set("long", @LONG 
�������ν��ɽ��������������ŵĶ��ϱ��ǹ�ɽ����������һ 
����ʯ�����������һ��С����
LONG 
	);
	set("exits", ([ 
		"southeast" : __DIR__"gushan",
	      "north"     : __DIR__"road7",
	])); 
	set("item_desc", ([ 
		"��С����" : "һ�����������صúܺõ�С����\n"
		ZJOBACTS2"�궴:enter dong\n",
	]));
	set("outdoors", "hangzhou"); 
	set("no_clean_up", 0);       
	setup(); 
} 
      
void init() 
{ 
	add_action("do_enter", "enter"); 
	add_action("do_enter", "zuan"); 
} 

int do_enter(string arg) 
{ 
	object me; 
	mapping fam; 
       
	me = this_player(); 
	if (! arg || arg == "") return 0; 
	if (arg == "dong") 
	{ 
		if (me->query("family/family_name") == "ؤ��")  
		{ 
			message("vision", 
				me->name() + "����ؤ�����ǹ���һ��������"
					     "�����˽�ȥ��\n", 
				environment(me), me); 
			me->move("/d/gaibang/underhz"); 
			message("vision", 
				me->name() + "�Ӷ������˽�����\n", 
				environment(me), ({me}) ); 
			return 1; 
		} 
		else  
			return notify_fail("��ôС�Ķ�������ý�ȥ��\n"); 
	} 
} 


