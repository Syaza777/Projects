import streamlit as st
from PIL import Image

def pageNLP():
    st.title("Welcome Madam!")
    st.caption("\n\n\nLets know what your students thinking about you")
    st.caption("\n\n\nHere's your graph for simple conclusion!")
    image = Image.open('nlp.png')
    st.image(image, caption='Students are very like you! Teaching methods was so interesting!')
    st.empty()

def pageAIRA():
    st.title("Welcome Madam!")
    st.caption("\n\n\nLets know what your students thinking about you")


def pageAIPM():
    st.title("Welcome Madam!")
    st.caption("\n\n\nLets know what your students thinking about you")


def pageEPI():
    st.title("Welcome Madam!")
    st.caption("\n\n\nLets know what your students thinking about you")

def pageLecturer():
    st.title("Welcome")
    st.caption("\n\n\nChoose your subject teaching")

    nlp = st.button("Natural Language Processing")
    aira = st.button("Artificial Intelligence in Robotic and Automation")
    aipm = st.button("Artificial Intelligence Project Management")
    epi = st.button("English in Professional Interaction")

    if nlp:
        pageNLP()

    elif aira:
        pageAIRA()

    elif aipm:
        pageAIPM()

    elif epi:
        pageEPI()

    # graph from data training
    # conclusion based on the graph



def pageStudent():
    st.header("Drop your opinion here!")
    with st.form("My opinion about subject:"):
        subject = st.selectbox("Subject:", ["Natural Language Processing","Artificial Intelligence in Robotic and Automation","Artificial Intelligence Project Management", "English For Professional Interaction"])
        opinion = st.text_area("Your opinion:")
        submitted = st.form_submit_button("SUBMIT")
        if submitted:
            st.write("Subject", subject, "Opinion", opinion)
            # send the opinion into excel for train n test model
            st.caption("Thank you for your opinion!")


def main():
    st.title("What do your students think of you as a lecturer?")
    st.caption("Their opinion can help you to become an excellent lecturer!")
    st.header("\n\n\n\n\n\n\n\nChoose your role")

    # button choose role
    lecturer = st.button("Lecturer")
    student = st.button("Student")

    if "lecturer_state" not in st.session_state:
        st.session_state.lecturer_state = False

    if "student_state" not in st.session_state:
        st.session_state.student_state = False

    # select page
    if lecturer or st.session_state.lecturer_state:
        pageLecturer()
        st.session_state.lecturer_state = True

    if student or st.session_state.student_state:
        pageStudent()
        st.session_state.student_state = True




if __name__ == "__main__":
    main()
