// wuhouci.c  ������� 
inherit ROOM; 
void create() 
{ 
	set("short", "�������"); 
	set("long", @LONG 
�������������������������������ڽ�һ����ǰ��������
��հ������и�������Ҳ�������������ڵ������ڵģ���ʫʥ�Ÿ���
����¶��ǧ��������������Ƶ�������£����������ϳ��ġ���������
���ǧ�ŷ緶��һ�����¡������¶��һ��С��(dong)��
LONG 
	);
	set("exits", ([ 
		"southdown" : __DIR__"liubeidian", 
	])); 
	set("item_desc", ([ 
		"��С����" : "һ���ڵ�Ǳ����صúܺõ�С����\n"
		ZJOBACTS2"�궴:enter dong\n",
	]));	
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
			me->move("/d/gaibang/undercd"); 
			message("vision", 
				me->name() + "�Ӷ������˽�����\n", 
				environment(me), ({me}) ); 
			return 1; 
		} 
		else  
			return notify_fail("��ôС�Ķ�������ý�ȥ��\n"); 
	} 
} 


