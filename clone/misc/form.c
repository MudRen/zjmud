// clone/misc/form
// Mud�շѵĵ����ʾ�
// Creat by Shure@tomud.com 2002-04-11
/*************************************
   database structure:
   ([
   id_1 : ([ step_1 : ({choice_1, choice_2,choice_3, ... }),
	     step_2 : ({choice_1, choice_2,choice_3, ... }),
	     ... ]),
   id_2 : ([ step_1 : ...
	     ... ]),
   ... ])
*************************************/

#include <ansi.h>

inherit COMBINED_ITEM;
inherit F_SAVE;

static mapping form = ([

	"��Ӵ�����mud�ж೤ʱ���ˣ�" : ({
		"һ�����¡�",
		"�������¡�",
		"�������¡�",
		"�������ϡ�" }),
		
	"�����ں�����mud��һ��ʲô���Ĺ�ϵ��" : ({
		"���ڻ����������е���ҡ�",
		"�������������������������Ѿ������ˡ�",
		"�������������������������Ѿ��巳��Ͷ����ͼ��������Ϸ�Ļ����ˡ�",
		"ѹ��û�����������ֻ��ͨ������������Щ�˽⡣",
		"��ǰ���������ң�������mud�ﵣ����ʦ��",
		"��ǰҲû��ô̫������mud��Ī������ؾ͵�����ʦ��" }),
		
	"����������г��Ϸǳ����еĽ�ɫ������ͼ�ν����������Ϸ����ħ�������������ࣩ��" : ({
		"���1-2��˽�һ�㡣",
		"���ŵ�ͼ�ν����������Ϸ�Ҷ�ȥ���Թ���",
		"����ͼ�ν����������Ϸ�ķ��ռ���ҡ�",
		"û�������" }),
		
	"����ͼ�ν����������Ϸ�ǳ����У���������£���ΪʲôҪѡ��������mud��" : ({
		"����������ֱ�ӡ�",
		"�ҽӴ�������Ϸ���Ǵ�������mud��ʼ�ģ��Ѿ�ϰ�߲���ϲ�������ַ�ʽ�ˡ�",
		"����mud��ͼ����Ϸ��ȸ����档",
		"��Ϊ����mud����ѵġ�",
		"���������������ϣ���������Ŀ�����" }),
		
	"��ͼ�ν����������Ϸ��ȣ����������mud��������Ҫ�����" : ({
		"����mud����̫���ˣ���Ϥ���ٵ�ָ���Լ�ѧϰzmudʹ�þ���Ҫ�ܳ�ʱ�䡣",
		"����mud�Ľ���̫���������Ѵӵ�һӡ����������ҡ�",
		"����mud����ʦ������ң�û��Լ����",
		"���ڵ�����mudû��̫������⣬������һ�׵��������ķ�ʽ��",
		"����û�б�֤��һ����Ϊ�¹������𻵻���������䶯����վ���޿�������޴�Ͷ�ߡ�",
		"���ڿ���û�б�֤�����������ȫ����ʦ�����飬û�ж�������Լ����",
		"���������������ϣ���������Ŀ�����" }),
		
	"��������漸���ϵ����������mud��ͼ��������Ϸ������������ϵ����ʣ�" : ({
		"DOSϵͳ��windowsϵͳ��",
		"�ż��߶���ϵ�걸��unixϵͳ�Ͳ���ֱ�۵�©�����win9x��",
		"ͬ����ĸ���������ӡ�",
		"�ܲ�����ˡ�",
		"���������������ϣ���������Ŀ�����" }),
		
	"���ڵ�����mud��Ҫʵ����Щ�������Ҫ�������������е������" : ({
		"��ʦ����͸���������򿪷�����Ϸ�������ϸ�ֿ��������ල���ơ�",
		"���������ĺ��ڿ������ϣ�ȷ����Ϸ�õ���ʱ�ĸ��¡�",
		"����������������������Ľ�����24Сʱ�ڵõ������Ļظ���",
		"����ȷ��ÿ�ձ��ݣ�������ǿ��ȫ���ϡ�",
		"���쿪�������͵���Ϸ���ơ�",
		"��������mud���ż���ʹ������ʽ�������ֱ�ӡ�",
		"�ͻ��ˣ���tomud��zmud������Ư���������Ի���ʹ֮����������һ����Ϸ��",
		"���������������ϣ���������Ŀ�����" }),
		
	"��������������������������£�����mud��ȡ�շ������У�����ȡʲô̬�ȡ�" : ({
		"Ϊ����mud���ѣ���������û�з��գ�",
		"��Ȼ�������������������mud�ķ���Ҳ�����ܣ�����ѡ����ѵĴպ���ɡ�",
		"����۸�Ͷ��ҽ��ѷ��㣬���Կ��ǽ��ܡ�",
		"�����Ŀ����ṩ������б�֤�ķ����һỨǮ����ϲ����mud��",
		"���������������ϣ���������Ŀ�����" }),
		
	"��������ڵ�����mud�¿����շ�վ������ں��������ȥ���ԣ�" : ({
		"��ʦ�����Ķ��ҹ�����ͬʱ���ڿ�����bug�������ܼ�ʱ��",
		"����շѺ����ҿ�վ���棬�г������ϣ��Ҿ�ѡ���ԡ�",
		"��������������ڵ�mud������ص�������ֵ������E-mail�������ҳ�ռ䣩���Ҿͻ�ѡ��",
		"���������Ҳ����������վ�㣬ȥ������mud��",
		"�����ܰ������ڵ�mud���������ݶ�ת������վ��",
		"���������������ϣ���������Ŀ�����" }),
		
	"�����������������ڵ�mud�¿����շ�վ����������º����շѷ�ʽ���Խ��ܣ�" : ({
		"����Ϸʱ��ĳ���ʵ�е����շ��ƶȡ�",
		"�����ĵ�������ȡ�·ѿ���",
		"ֻ���ܽ����·ѿ�" }),
		
	"��ϣ��ͨ�����ַ�ʽ���ɷ��ã�" : ({
		"ͨ����ʽ�����ʻ���ֵ��",
		"����ֱ�ӻ������ѣ����������ʺš�",
		"��ס����������걨��ͤ������Ϸ��������",
		"�������̳ǹ���ʵ����������ͻ����š�" }),	
	]);

static string *k_form  = ({
	"��Ӵ�����mud�ж೤ʱ���ˣ�",
	"�����ں�����mud��һ��ʲô���Ĺ�ϵ��",
	"����������г��Ϸǳ����еĽ�ɫ������ͼ�ν����������Ϸ����ħ�������������ࣩ��",
	"����ͼ�ν����������Ϸ�ǳ����У���������£���ΪʲôҪѡ��������mud��",
	"��ͼ�ν����������Ϸ��ȣ����������mud��������Ҫ�����",
	"��������漸���ϵ����������mud��ͼ��������Ϸ������������ϵ����ʣ�",
	"���ڵ�����mud��Ҫʵ����Щ�������Ҫ�������������е������",
	"��������������������������£�����mud��ȡ�շ������У�����ȡʲô̬�ȡ�",
	"��������ڵ�����mud�¿����շ�վ������ں��������ȥ���ԣ�",
	"�����������������ڵ�mud�¿����շ�վ����������º����շѷ�ʽ���Խ��ܣ�",
	"��ϣ��ͨ�����ַ�ʽ���ɷ��ã�",
	});     
	
static string *index   = ({ "A", "B", "C", "D", "E", "F", "G", "H" });
static mapping answers = ([]);
static string *options;
mapping sheet;

void setup();
void set_amount(int i);
int  do_start();
void QA_step( int step );
void decide_choice( string answer, object me, int step );
void do_refer( string yn, object me );
void done_self_opinion( object me, int step, string text );
void query_site( string site, object me );
void save_sheet( object me, mapping answers );
mixed query_sheet();

void create()
{
	set_name(YEL"����MUD�����ʾ�"NOR, ({ "questionary", "wenjuan" }) );
	set("long", "����һ���й�����mud��չ�ĵ����ʾ�\n"
		    "����mud�������ֱ��ֵ�������Ϸ�ˣ�˵�ü�Щ��Ҳ�������������������Ϸ��\n"
		    "��ʱ��û��ʲô�ã�����ԭ���У��ͱ��������ˡ�\n"
		    "����"HIR"start"NOR"ָ���ʼ��������ش�\n" );
	set_weight(1);
	set( "base_weight", 1 );
	set("unit","��");
	set("base_unit","��");
	set_amount(1);
	setup();
}

void setup()
{
	if ( !clonep() )
		restore();
}

void init()
{
	if ( clonep() )
		add_action( "do_start", "start" );
}

string query_save_file()
{
	return DATA_DIR + "questionary";
}

void set_amount( int i )
{
	if ( i < 0 )
		error( "set_amount as null!\n" );
	if ( i == 0 )
		destruct( this_object() );
	else
		amount = 1;
}

int do_start()
{
	sheet = copy( base_name( this_object() )->query_sheet() );
	if ( mapp( sheet ) && !undefinedp( sheet[this_player()->query( "id" )] ) )
	{
		write( "�Բ������Ѿ���д�������ʾ��ˣ���л���һ��֧�֣�\n" );
		destruct( this_object() );
		return 1;
	}
	QA_step(0);
	return 1;
}

void QA_step( int step )
{
	int    i, j;
	string *choice, item;
		
	if ( step >= sizeof( form ) )
	{
		write( "����Ѿ���д��ϣ��������Ƿ�����ύ��(y/n)" );
		input_to( "do_refer", this_player() );
		return ;
	}
	item   = k_form[step];
	choice = form[item];
	j      = sizeof(choice);
	
	write( HIG + ( step + 1 ) + "��" + item + "\n\n" + NOR );
	for ( i = 0; i < j; i ++ )
		write( index[i] + " " + choice[i] +"\n" );

	write( "\n���������ѡ��(A��B��C��D)\n"
	       "�����ѡ���÷ֺŸ���ÿ��ѡ�(�磺A��B��D)\n" );    
	input_to( "decide_choice", this_player(), step );
}

void decide_choice( string answer, object me, int step )
{
	int     i, j, error;
	string *v;
	
	answer  = replace_string( answer, " ", "" ); 
	v = form[ k_form[step] ];
	
	if (strsrch( answer, "��" ) == -1 )
	{
		j = member_array( answer, index );

		if ( j == -1 || ( j + 1 ) > sizeof( v ) )
		{
			write( "\n��"HIR"��ȷ"NOR"�������ѡ��(A��B��C��D)\n"
			       "�����ѡ���÷ֺŸ���ÿ��ѡ�(�磺A��B��D)\n" );	      
			input_to( "decide_choice", me, step );
			return;
		}
		else
		{
			if ( v[ j ] == "���������������ϣ���������Ŀ�����" )
				me->edit((: done_self_opinion, me, step :));
			else
			{
				options = ({ answer });
				answers[step] = options;
				QA_step( step + 1 );
			}
			return;
		}
	}
	options = explode( answer, "��" );
	error   = 0;	
	for ( i = 0; i < sizeof( options ); i ++ )
	{
		if ( ( j = member_array( options[i], index ) ) == -1
		     || ( j + 1 ) > sizeof( v )
		     || v[ j ] == "���������������ϣ���������Ŀ�����" )
		{
			error ++;
			break;
		}
	}
	if ( error )
	{
		write( "\n��"HIR"��ȷ"NOR"�������ѡ��(A��B��C��D...)\n"
		       "�����ѡ���÷ֺŸ���ÿ��ѡ����磺C��E��F��\n" );
		options = ({});    
		input_to( "decide_choice", me, step );
		return;
	}
	answers[step] = options;
	QA_step( step + 1 );
}

void do_refer( string yn, object me )
{
	if ( yn == "Y" || yn == "y" )
	{
		write( "��������Ŀǰ���ڵĹ��Һͳ��У��磺�й�������" );
		input_to( "query_site", me );
		return;
	}
	if ( yn != "N" && yn != "n" )
	{
		write( "����Ѿ���д��ϣ��������Ƿ�����ύ��(y/n)\n" );
		input_to( "do_refer", me );
		return;
	}
	answers  = ([]);
	options = ({}); 
	write( "�����ύ��\n������д���������startָ�\n" );
	return;
}

void done_self_opinion( object me, int step, string text )
{
	options = ({ "self_opinion: " + text });
	answers[step] = options;
	QA_step( step + 1 );
}

void query_site( string site, object me )
{
	if ( !stringp( site ) || site == "" )
	{
		write( "��������Ŀǰ���ڵĹ��Һͳ��У��磺�й�������\n" );
		input_to( "query_site", me );
	       // return;
	}
	answers[ "site" ] = site;
	//me->save_sheet( me, answers );
	write( "������ύ��лл���֧�֣�\n" );
	destruct( this_object() );
	
}

void save_sheet( object me, mapping answers )
{
	if ( !clonep() )
	{
		sheet[ me->query("id") ] = copy(answers);
		save();
	}
}

mixed query_sheet()
{
	if ( !clonep() )
		return sheet;
	return 0;
}
